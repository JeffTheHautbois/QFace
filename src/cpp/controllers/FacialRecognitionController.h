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

  void loadModel(const FileStorage& fs){

  }

  void saveModel(FileStorage& fs){

  }

  void trainModel(InputArrayOfArrays src, InputArray labels){

  }

  void cropAndSaveFaceTemporary(Image& inputImage){

  }

  void identify(InputArray src, int& label, double& confidence){

  }

  void createFaceRecognizer(int num_components=0, double threshold=DBL_MAX){

  }

private:
  cv::Mat imageData; // the image stored as a Mat
};




#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
