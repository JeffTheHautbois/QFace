#include <emscripten.h>
#include <iostream>
#include <string>

#include "controllers/DuckCropperController.h"
#include "models/MatModel.h"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"


/*
 * Crops the duck image into a square. Does not modify the original image.
 */
std::string croppedDuckImageAsByteString(int length) {
  cv::Mat duckImage;
  loadImageIntoMat("data/duck.bmp", &duckImage);

  if (duckImage.empty()) {
    std::cout << "Was not able to load the duck bitmap" << std::endl;
    std::string empty = "";
    return empty;
  }

  // This part should be handled by the Model.
  const std::string filePath = "data/haarcascade_frontalface_default.xml";
  std::cout << filePath << std::endl;
  cv::CascadeClassifier face;
  face.load(filePath);

  // The actual cropping occurs here.
  cv::Rect regionOfInterest(0, 0, length, length);
  cv::Mat croppedDuckImage = duckImage(regionOfInterest);

  return convertMatToByteString(croppedDuckImage);
}
