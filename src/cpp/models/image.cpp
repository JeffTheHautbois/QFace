#include <string>
#include <vector>
#include "Image.h"
#include "MatModel.h"
// Constructor given cv::Mat
Image::Image(cv::Mat matrix) : imageData(matrix){
}

// Constructor given base64 string
Image::Image(std::string base64EncodedImage){

}

// Constructor given byte vector
Image::Image(std::vector<unsigned char> imageBytes){

}

// Data accessor
cv::Mat Image::getData() const{
  return imageData;
}

std::vector<unsigned char> Image::asBytes(){
  return convertMatToByteString(imageData);
}

