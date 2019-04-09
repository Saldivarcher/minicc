#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <istream>
#include <string>
#include <vector>

class Lexer {
private:
  // Holds the content of the current file being read in
  std::istream &buffer;

  // Holds all the tokens that were generated from
  std::vector<Token> tokens;

  // Get the character in the buffer
  char advance() {
    char ch;
    buffer.get(ch);
    if (buffer.eof())
      return EOF;
    return ch;
  }

  char peek() { return buffer.peek(); }

public:
  Lexer(std::istream &buffer) : buffer(buffer) {}

  std::vector<Token> lex();
};

#endif
