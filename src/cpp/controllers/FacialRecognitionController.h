#ifndef SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_

#include <vector>
#include "models/Image.h"
#include "opencv2/core.hpp"

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer(int radius, int neighbors, int grid_x, int grid_y, double threshold);
  ~FacialRecognizer(); // Destructor

  void loadModel();

  void saveModel();

  void trainModel(const cv::InputArray& src);

  void identify(Image& src, int& label, double& confidence);

  void updateModel(cv::InputArrayOfArrays& src)

private:
  std::vector<Image> images;
  std::vector<int> labels;
  cv::face::FaceRecognizer* model;
};




#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
