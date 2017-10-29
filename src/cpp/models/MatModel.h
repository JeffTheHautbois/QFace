#ifndef SRC_CPP_MODELS_MATMODEL_H_
#define SRC_CPP_MODELS_MATMODEL_H_

#include <iostream>
#include <vector>
#include <string>

#include "opencv2/core.hpp"

void loadImageIntoMat(const std::string& filename, cv::Mat* mat);
std::string convertMatToByteString(const cv::Mat& mat);
void convertMatToByteVector(const cv::Mat& mat,
                            std::vector<unsigned char>* buffer);

#endif  // SRC_CPP_MODELS_MATMODEL_H_
