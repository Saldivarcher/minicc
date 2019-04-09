#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>
#include <string>
#include <unordered_map>

enum TokenKind {
  TK_NUM,      // Number literal
  TK_STR,      // String literal
  TK_CLIT,     // Char literal
  TK_IDENT,    // Identifier
  TK_ARROW,    // ->
  TK_EXTERN,   // "extern"
  TK_TYPEDEF,  // "typedef"
  TK_INT,      // "int"
  TK_CHAR,     // "char"
  TK_VOID,     // "void"
  TK_STRUCT,   // "struct"
  TK_BOOL,     // "_Bool"
  TK_IF,       // "if"
  TK_ELSE,     // "else"
  TK_FOR,      // "for"
  TK_DO,       // "do"
  TK_WHILE,    // "while"
  TK_SWITCH,   // "switch"
  TK_CASE,     // "case"
  TK_BREAK,    // "break"
  TK_CONTINUE, // "continue"
  TK_EQ,       // ==
  TK_NE,       // !=
  TK_LE,       // <=
  TK_GE,       // >=
  TK_LOGOR,    // ||
  TK_LOGAND,   // &&
  TK_SHL,      // <<
  TK_SHR,      // >>
  TK_INC,      // ++
  TK_DEC,      // --
  TK_MUL_EQ,   // *=
  TK_DIV_EQ,   // /=
  TK_MOD_EQ,   // %=
  TK_ADD_EQ,   // +=
  TK_SUB_EQ,   // -=
  TK_SHL_EQ,   // <<=
  TK_SHR_EQ,   // >>=
  TK_AND_EQ,   // &=
  TK_XOR_EQ,   // ^=
  TK_OR_EQ,    // |=
  TK_RETURN,   // "return"
  TK_SIZEOF,   // "sizeof"
  TK_ALIGNOF,  // "_Alignof"
  TK_TYPEOF,   // "typeof"
  TK_PARAM,    // Function-like macro parameter
  TK_SYM,      // Symbol
  TK_EOF,      // End marker
};

// Structure that holds all the information of the token
class Token {
public:
  TokenKind kind;

  // String identifier
  std::string identifier;

  // Number  literal
  int val = 0;

  // Character literal
  std::string cliteral;

  // String literal
  std::string literal;

  // Symbol, this is a string because of multi-letter symbols
  std::string symbol;

  friend std::ostream &operator<<(std::ostream &, const Token &);

  Token(TokenKind kind) : kind(kind) {}
  Token(TokenKind kind, int val) : kind(kind), val(val) {}

  static TokenKind getSymbolToken(const std::string &);
  static TokenKind getKeywordToken(const std::string &);
};

#endif
