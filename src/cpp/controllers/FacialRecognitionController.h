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
 * cannot do by itself. Utilizes functions related to a
 * LBPHFaceRecognizer for updating the model, and constructs
 */

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer();

  // Load saved model state from database and set current model to it
  void loadModel();

  // Save current model state to database
  void saveModel();

  // Fetch all customer image and student ID pairs and train model for
  // identifying customers in database
  void trainModel();

  // Identify a customer in a given image
  int identify(Image& src, double* confidence);

  // Update current model to include new images. Images and labels must be
  // passed in from the view
  void updateModel(std::vector<Image>& newImages, std::vector<int>& newLabels);

private:
  // The current active FaceRecognizer "model"
  cv::Ptr<cv::face::FaceRecognizer> model;
  // Persistent data storage file format (YAML)
  const std::string persistenceFiletype;
};


#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
