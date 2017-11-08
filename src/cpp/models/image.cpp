#include <string>
#include <vector>
#include "Image.h"
#include "MatModel.h"
#include "base64.h"
// Constructor given cv::Mat
Image::Image(cv::Mat matrix) : imageData(matrix){
}

// Constructor given base64 string
Image::Image(std::string base64EncodedImage){
  std::vector<unsigned char> imageBytes = base64::base64_decode(base64EncodedImage);
  cv::Mat data_mat(imageBytes,true);
  imageData = data_mat;
}

// Constructor given byte vector
Image::Image(std::vector<unsigned char> imageBytes){
  cv::Mat data_mat(imageBytes,true);
  imageData = data_mat;
}

// Data accessor
cv::Mat Image::getData() const{
  return imageData;
}

std::vector<unsigned char> Image::asBytes(){
  return convertMatToByteString(imageData);
}

std::string Image::asBase64(){
  std::vector<unsigned char> imageBytes = convertMatToByteString(imageData);
  std::string encodedData = base64::base64_encode(&imageBytes[0], imageBytes.size());
  return encodedData;
}