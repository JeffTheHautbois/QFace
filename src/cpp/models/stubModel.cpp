#include <iostream>
#include <fstream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

#include "models/stubModel.h"


int loadDuckImage() {
  std::cout << "Starting file read" << std::endl;

  std::ifstream image("data/1200px-Mallard2.jpg", cv::IMREAD_COLOR);
  if (image) {
    image.seekg(0, image.end);
    int imageSize = image.tellg();
    std::cout << "The image file is " << imageSize << " bytes." << std::endl;
    image.close();
  } else {
    std::cout << "Could not open this file.";
  }

  return 0;
}
