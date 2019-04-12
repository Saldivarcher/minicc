#include "Lexer.h"
#include <iostream>

void Lexer::eatWhitespace(char &ch) {
  while (std::isspace(ch))
    ch = advance();
}

void Lexer::eatLineComment(char &ch) {
  while (ch != '\n' || ch != EOF)
    ch = advance();
}

void Lexer::eatCharLiteral(char &ch) {
  // Eat char
  ch = advance();
  std::string clit(1, ch);

  Token tok_char(TK_CLIT);
  if (ch != '\\') {
    tok_char.cliteral = clit;
    ch = advance();
  } else {
    // Escaped characters are handled here

    // Eat the character after '\'
    ch = advance();
    clit += ch;
    tok_char.cliteral = clit;
    // Go to next char which should be '
    ch = advance();
  }
  tokens.push_back(tok_char);

  // Eat other '
  if (ch != '\'') {
    std::cerr << "No \"'\"!" << std::endl;
    std::exit(4);
  }
}

void Lexer::eatStringLiteral(char &ch) {
  std::string literal;
  ch = advance();
  while (ch != '"') {
    literal += ch;
    ch = advance();
  }
  Token tok_lit(TK_STR);
  tok_lit.literal = literal;
  tokens.push_back(tok_lit);
}

void Lexer::eatIdentifier(char &ch) {
  auto make_token = [this](TokenKind tok_kind, const std::string &identifier) {
    Token tok_ident(tok_kind);
    tok_ident.identifier = identifier;
    tokens.push_back(tok_ident);
  };

  std::string identifier;
  while (std::isalnum(ch) || ch == '_') {
    identifier += ch;
    ch = advance();
  }
  if (auto keyword = Token::getKeywordToken(identifier)) {
    make_token(*keyword, identifier);
  } else {
    make_token(TK_IDENT, identifier);
  }
}

void Lexer::eatNumber(char &ch) {
  std::string digit;
  while (isdigit(ch)) {
    digit += ch;
    ch = advance();
  }

  Token tok_digit(TK_NUM, std::stoi(digit));
  tokens.push_back(tok_digit);
}

void Lexer::eatSymbol(char &ch) {
  auto make_token = [this](TokenKind tok_kind, const std::string &symbol) {
    Token tok_symbol(tok_kind);
    tok_symbol.symbol = symbol;
    tokens.push_back(tok_symbol);
  };

  std::string symbol(1, ch);
  // Multi-letter symbol
  if (is_symbol(peek())) {
    ch = advance();
    while (is_symbol(ch)) {
      symbol += ch;
      ch = advance();
    }

    if (auto Tok = Token::getSymbolToken(symbol)) {
      make_token(*Tok, symbol);
    } else {
      // Function calls with no params handled here: '();'
      for (const auto &c : symbol)
        make_token(TK_SYM, std::string(1, c));
    }

  } else {
    // Single-letter symbols
    make_token(TK_SYM, symbol);
  }
}

// TODO: Add block comments
std::vector<Token> Lexer::lex() {
  char ch = advance();
  while (ch != EOF) {

    // Skip whitespace
    if (std::isspace(ch))
      eatWhitespace(ch);

    // Eat line comments
    if (ch == '/' && peek() == '/')
      eatLineComment(ch);

    // Character literal
    if (ch == '\'') {
      eatCharLiteral(ch);
      ch = advance();
    }

    // String literal
    if (ch == '"') {
      eatStringLiteral(ch);
      ch = advance();
    }

    // Eat keywords or identifiers
    if (std::isalpha(ch) || ch == '_')
      eatIdentifier(ch);

    // Eat Number
    if (std::isdigit(ch))
      eatNumber(ch);

    // Eat symbols
    if (is_symbol(ch)) {
      eatSymbol(ch);
      ch = advance();
    }
  }

  return tokens;
}
