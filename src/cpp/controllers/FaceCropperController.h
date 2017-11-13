#ifndef SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_

#include <iostream>
#include <string>

#include "models/Image.h"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class FaceCropper{
 public:
  FaceCropper(); // Constructor: automatically loads cascadeClassifier
  std::string cropFaceAndSaveInTemporaryStorage(Image& passedImage); // Crops the image and returns a Base64 String
private:
  cv::CascadeClassifier face; // Cascade classifier object
  void loadCascadeClassifier(const std::string&); // Pre-load the cascade classifier from an xml file
};

class FaceDetectionException {
public:
  FaceDetectionException(const std::string&);
  std::string what() const;
private:
  std::string message;
};

#endif  // SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
