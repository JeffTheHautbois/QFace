#include <iostream>
#include "test/test.h"

int main() {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  std::cout << "It worked!" << "\n";
  return 0;
}
