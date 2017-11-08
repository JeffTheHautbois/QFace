#ifndef SRC_CPP_MODELS_IMAGE_H_
#define SRC_CPP_MODELS_IMAGE_H_

#include <string>
#include <vector>
#include "opencv2/core.hpp"

class Image {
public:
  Image(cv::Mat matrix);
  Image(std::string base64EncodedImage);
  Image(std::vector<unsigned char> imageBytes);

  cv::Mat asMat() const; // accessor
  std::string asBase64();
  std::vector<unsigned char> asBytes();

private:
  cv::Mat imageData; // the image stored as a Mat
};

#endif /* SRC_CPP_MODELS_IMAGE_H_ */
