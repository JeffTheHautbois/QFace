#ifndef SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#include <string>
#include <vector>
#include "opencv2/core.hpp"
#include "Image.h"

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer(cv::Mat matrix);

  void loadDataSet(){

  }

  void loadModel(const cv::FileStorage& fs){

  }

  void saveModel(cv::FileStorage& fs){

  }

  void trainModel(cv::InputArrayOfArrays src, cv::InputArray labels){

  }

  void cropAndSaveFaceTemporary(Image& inputImage){

  }

  void identify(cv::InputArray src, int& label, double& confidence){

  }

  void createFaceRecognizer(int num_components=0, double threshold=DBL_MAX){

  }

private:
  cv::Mat imageData; // the image stored as a Mat
};




#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
