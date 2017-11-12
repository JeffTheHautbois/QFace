#ifndef SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_

#include <iostream>
#include <string>

#include "models/Image.h"
#include "opencv2/core.hpp"

cv::CascadeClassifier loadCascadeClassifier(const std::string&);
std::string cropFaceImageAsByteString(Image& passedImage);

#endif  // SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
