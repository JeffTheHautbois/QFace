#ifndef SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_

#include <vector>
#include "models/Image.h"
#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/face.hpp"

/*
 * This class will be utilized as the "core" algorithm for
 * the project. It creates a cv::FaceRecognizer and allows
 * the team to use it through this "wrapper" class. This
 * class also implements saving and loading model states
 * from raw XML strings, which the cv::FaceRecognizer
 * cannot do by itself.
 */

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer();

  // Load saved model state from database and set current model to it
  void loadModel();

  // Save current model state to database
  void saveModel();

  // Train the model
  void trainModel();

  // Identify a customer in a given image
  int identify(Image& src, double* confidence);

  // Update current model to include new images
  void updateModel(cv::InputArrayOfArrays& src);

private:
  std::vector<Image> images;
  std::vector<int> labels;
  cv::Ptr<cv::face::FaceRecognizer> model;
  const std::string persistenceFiletype;
};


#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
