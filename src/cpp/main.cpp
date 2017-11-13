#include <iostream>
#include "test/test.h"
#include "views/FaceCropperView.h"
#include "models/Image.h"
#include <string>
#include <opencv2/core.hpp>

int main() {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  std::string output = detectCropFace();
  std::cout << output << std::endl;

  std::cout << "It worked!" << "\n";
  return 0;
}
