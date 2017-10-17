#include <iostream>
#include <fstream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "models/stubModel.h"


cv::Mat loadDuckImage() {
  return cv::imread("data/tiny_duck.bmp");
}
