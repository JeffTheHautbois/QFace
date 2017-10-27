#include "models/MatModel.h"

#include <iostream>
#include <vector>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"


/*
 * It might make sense for the model to create a wrapper class around a Mat object.
 * For instance, if we have a TurboMat class, it will have a toString and toBytes method.
 * (or whatever the best equivalent C++ practice is)
 */

/*
 * Loads an image based on the filename.
 */
void loadImageIntoMat(const std::string& filename, cv::Mat* mat) {
  *mat = cv::imread(filename);
}

/*
 * Converts a mat object into a byte string.
 */
std::string convertMatToByteString(const cv::Mat& mat) {
  /*
   * There are probably better ways of doing this. This was a hack, so
   * if a more efficient way of doing this exists, it should ideally be done.
   *
   * Another method to include might be encodeMatToBase64 string. Right now,
   * the conversion between this string to base64 is done using a built in JS
   * function called btoa() in the views. Ideally, it should either be done
   * here or in a separate method.
   */
  std::vector<unsigned char> buffer;
  convertMatToByteVector(mat, &buffer);

  std::stringstream stream;
  for (unsigned int i = 0; i < buffer.size(); i++) {
    stream << buffer[i];
  }

  return stream.str();
}

/*
 * Uses openCV's built in imencode function to convert a Mat into a bitmap.
 */
void convertMatToByteVector(const cv::Mat& mat,
                            std::vector<unsigned char>* buffer) {
  cv::imencode(".bmp", mat, *buffer);
}
