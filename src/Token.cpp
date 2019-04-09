#include "Token.h"

std::ostream &operator<<(std::ostream &os, const Token &tok) {
  os << "ident:    " << tok.identifier << std::endl
     << "kind:     " << tok.kind << std::endl
     << "value:    " << tok.val << std::endl
     << "literal:  " << tok.literal << std::endl
     << "symbol:   " << tok.symbol << std::endl
     << "cliteral: " << tok.cliteral << std::endl;

  return os;
}

// TODO: Don't initialize the map everytime the function is hit, figure out how
// to do it within the class
TokenKind Token::getSymbolToken(const std::string &symbol) {
  std::unordered_map<std::string, TokenKind> symbols = {
      {"<<=", TK_SHL_EQ}, {">>=", TK_SHR_EQ}, {"!=", TK_NE},
      {"&&", TK_LOGAND},  {"++", TK_INC},     {"--", TK_DEC},
      {"->", TK_ARROW},   {"<<", TK_SHL},     {"<=", TK_LE},
      {"==", TK_EQ},      {">=", TK_GE},      {">>", TK_SHR},
      {"||", TK_LOGOR},   {"*=", TK_MUL_EQ},  {"/=", TK_DIV_EQ},
      {"%=", TK_MOD_EQ},  {"+=", TK_ADD_EQ},  {"-=", TK_SUB_EQ},
      {"&=", TK_AND_EQ},  {"^=", TK_XOR_EQ},  {"|=", TK_OR_EQ}};

  return symbols.at(symbol);
}

TokenKind Token::getKeywordToken(const std::string &keyword) {
  std::unordered_map<std::string, TokenKind> keywords = {
      {"_Alignof", TK_ALIGNOF},
      {"_Bool", TK_BOOL},
      {"break", TK_BREAK},
      {"case", TK_CASE},
      {"char", TK_CHAR},
      {"continue", TK_CONTINUE},
      {"do", TK_DO},
      {"else", TK_ELSE},
      {"extern", TK_EXTERN},
      {"for", TK_FOR},
      {"if", TK_IF},
      {"int", TK_INT},
      {"return", TK_RETURN},
      {"sizeof", TK_SIZEOF},
      {"struct", TK_STRUCT},
      {"switch", TK_SWITCH},
      {"typedef", TK_TYPEDEF},
      {"typeof", TK_TYPEOF},
      {"void", TK_VOID},
      {"while", TK_WHILE}};

  return keywords.at(keyword);
}
