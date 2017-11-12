#ifndef SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_

#include <iostream>
#include <string>

#include "models/Image.h"
#include "opencv2/core.hpp"

cv::CascadeClassifier loadCascadeClassifier(const std::string&); // Pre-load the cascade classifier from an xml file
std::string cropFaceImageAsByteString(Image& passedImage, cv::CascadeClassifier); // Crops the image and returns it as a byte string

#endif  // SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
