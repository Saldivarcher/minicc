#include "Lexer.h"
#include <cstring>
#include <iostream>

std::vector<Token> Lexer::lex() {

  auto is_symbol = [](char ch) -> bool {
    if (std::strchr("+-*/;=(),{}<>[]&.!?:|^%~#", ch))
      return true;
    return false;
  };

  char ch = advance();
  while (ch != EOF) {

    // Skip whitespace
    if (std::isspace(ch)) {
      while (std::isspace(ch))
        ch = advance();
    }

    // Eat line comments
    if (ch == '/' && peek() == '/') {
      while (ch != '\n' || ch != EOF)
        ch = advance();
    }

    // Character literal
    if (ch == '\'') {
      // Eat char
      ch = advance();
      std::string clit(1, ch);

      Token tok_char(TK_CLIT);
      if (ch != '\\') {
        tok_char.cliteral = clit;
        ch = advance();
      } else {
        // Escaped characters are handled here
        ch = advance();
        clit += ch;
        tok_char.cliteral = clit;
      }
      tokens.push_back(tok_char);

      // Eat other '
      if (peek() != '\'') {
        std::cerr << "No \"'\"!" << std::endl;
        // std::exit(4);
      }

    }

    // String literal
    if (ch == '"') {
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

    // Eat keywords or identifiers
    if (std::isalpha(ch) || ch == '_') {
      std::string identifier;
      while (std::isalnum(ch) || ch == '_') {
        identifier += ch;
        ch = advance();
      }
      Token tok_ident(TK_IDENT);
      tok_ident.identifier = identifier;
      tokens.push_back(tok_ident);
    }

    // Eat Number
    if (std::isdigit(ch)) {
      std::string digit;
      while (isdigit(ch)) {
        digit += ch;
        ch = advance();
      }

      Token tok_digit(TK_NUM, std::stoi(digit));
      tokens.push_back(tok_digit);
    }

    // Eat symbols
    if (is_symbol(ch)) {
      std::string symbol(1, ch);
      // Multi-letter symbol
      if (is_symbol(peek())) {
        ch = advance();
        while (is_symbol(ch)) {
          symbol += ch;
          ch = advance();
        }
        auto Tok = Token::getSymbolToken(symbol);
        Token tok_symbol(Tok);
        tok_symbol.symbol = symbol;
        tokens.push_back(tok_symbol);
      } else {
        Token tok_symbol(TK_SYM);
        tok_symbol.symbol = symbol;
        tokens.push_back(tok_symbol);
      }
      ch = advance();
    }
  }

  return tokens;
}
