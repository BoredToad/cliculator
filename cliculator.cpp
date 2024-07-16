#include "cliculator.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Bad input!\nUsage:\n\t'cliculator --option <equation>'\n";
    return 1;
  }
  std::string opt = argv[1];

  if (opt == "-h") {
    std::cout << "Options:\n\t'-c'\t--calculates the value of expressions "
                 "without variables\n";

  } else if (opt == "-c" && argc == 3) {
    std::string equation = argv[2];
    std::cout << equation << "\t->\n"
              << cliculator::calculate(equation) << "\n";

  } else {
    std::cout << "Bad input!\n";
    return 2;
  }

  return 0;
}
