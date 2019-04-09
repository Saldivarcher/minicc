#include "Driver.h"
#include "Error.h"
#include <filesystem>
#include <fstream>

void Driver::run(const char *filename) {
  auto path = std::filesystem::path(filename).extension();

  if (path.generic_string() != ".c")
    error::Error("This is not a valid c file!\n", 2);

  std::ifstream filestream(filename);
  if (!filestream.is_open())
    error::Error("This is not a valid c file!\n", 3);

  Lexer l(filestream);
  auto tokens = l.lex();

  for (int i = 0; i < tokens.size(); i++) {
    std::cout << tokens[i] << std::endl;
  }
}
