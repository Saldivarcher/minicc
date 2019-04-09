#include "Driver.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Need to provide more than one argument!\n";
    std::exit(1);
  }
  Driver d;
  d.run(argv[1]);
}
