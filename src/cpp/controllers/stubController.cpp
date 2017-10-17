#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"


#include "controllers/stubController.h"
#include "models/stubModel.h"

#include <emscripten.h>


/**
 * This method is supposed to open the duck bitmap (handled in the model), crop it
 * to a 100x100px, convert it to a base64 bitmap string, and send it upwards for the view
 * to handle.
 *
 * The cropping already works, so it has been disabled (it is commented out below).
 * The issue is converting to the bitmap array to the base64 string has not yet been solved.
 *
 * If you open the file data/b64.txt, you should see what the base64 converted version of this
 * bitmap file is supposed to look like. If you click the button on the app and open your
 * javascript console, you well get a textual output of what string you are returning here looks like
 * once it reaches the frontend.
 */
std::string getCroppedDuckImage() {
  std::cout << "Attempting to load duck image." << std::endl;

  cv::Mat duckImage = loadDuckImage();
  if (duckImage.empty()) {
    std::cout << "Was not able to create a cv::Mat from the duck bitmap" << std::endl;
    std::string empty = "";
    return empty;
  }

  std::cout << "The duck image was loaded!" << std::endl;
  std::cout << "The dimensions are " << duckImage.rows << "x" << duckImage.cols << "px." << std::endl;

  // This stuff is for cropping the duck image. It works, but ignore it for now. You can uncomment it
  // once the convertion to base64 is done.
  // std::cout << "Attempting to crop into 100x100px image." << std::endl;
  // cv::Rect regionOfInterest(0, 0, 100, 100);
  // duckImage = duckImage(regionOfInterest);
  //
  // std::cout << "The new dimensions are " << duckImage.rows << "x" << duckImage.cols << "px." << std::endl;

  // If I understand correctly, the code below converts from a Mat to a bitmap, and stores it
  // in buffer.
  std::vector<uchar> buffer;
  cv::imencode(".bmp", duckImage, buffer);

  // This was my attempt to convert the bitmap into a string. It does not work.
  // Once this works, this stuff should be extracted into a separate
  // function/class in the models.
  std::cout << "Converting to string" << std::endl;
  std::string duckString = "";
  for (unsigned int i = 0; i < buffer.size() - 3; i+= 3) {
      duckString += buffer[i];
  }

  return duckString;
}
