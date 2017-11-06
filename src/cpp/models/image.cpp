#include <string>
#include <vector>
#include "Image.h"
#include "MatModel.h"

Image::Image(cv::Mat matrix){
  imageData = matrix;
}

cv::Mat Image::getData() const{
  return imageData;
}

std::vector<unsigned char> Image::asBytes(){
  return convertMatToByteString(imageData);
}

