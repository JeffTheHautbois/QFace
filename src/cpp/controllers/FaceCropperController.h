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
  void cropFaceAndSaveInTemporaryStorage(Image& passedImage); // Crops the image and returns a Base64 String
  void getFaceROI(Image& passedImage, int* x, int*y, int* width, int* height); // Find the rectangle that bounds a detected face for webcam
private:
  cv::CascadeClassifier face; // Cascade classifier object
  void loadCascadeClassifier(const std::string&); // Pre-load the cascade classifier from an xml file
  cv::Rect getFaceROI(cv::Mat& grayImg); // Find the rectangle that bounds a detected face for cropping
};

class FaceDetectionException {
public:
  FaceDetectionException(const std::string& msg) : message(msg) {};
  std::string what() const { return message; };
private:
  std::string message;
};

#endif  // SRC_CPP_CONTROLLERS_FACECROPPERCONTROLLER_H_
