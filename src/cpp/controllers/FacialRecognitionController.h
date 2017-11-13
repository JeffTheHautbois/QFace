#ifndef SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_

#include <vector>
#include "models/Image.h"
#include "opencv2/core.hpp"

using namespace cv;

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer();

  void loadDataSet();

  void loadModel(const cv::FileStorage& fs);

  void saveModel(cv::FileStorage& fs);

  void trainModel(cv::InputArrayOfArrays src, cv::InputArray labels);

  void cropAndSaveFaceTemporary(Image& inputImage);

  void identify(cv::InputArray src, int& label, double& confidence);

  void createFaceRecognizer(int num_components, double threshold);
private:
  std::vector<Image> images;
  std::vector<int> labels;
  Ptr<FacialRecognizer> model;
};




#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
