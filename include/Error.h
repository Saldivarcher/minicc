#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>
#include <iostream>

namespace error {

// Generic `Error` function that exits when used
void Error(const char *ErrMsg, unsigned ErrCode) {
  std::cerr << ErrMsg << std::endl;

  exit(ErrCode);
}

}; // namespace error

#endif
