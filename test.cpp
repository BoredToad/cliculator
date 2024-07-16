#include "cliculator.h"
#include <iostream>
#include <string>

using namespace cliculator;
int main() {
  std::cout << "TEST:\n"
            << "Handles basic arithmetic: "
            << std::to_string("9" == calculate("5 + 4")) << "\n";
  return 0;
}
