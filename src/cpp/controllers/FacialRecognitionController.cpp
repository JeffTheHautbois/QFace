#include <iostream>
#include <string>
#include <emscripten.h>
#include "opencv2/face.hpp"
#include "FacialRecognitionController.h"

FacialRecognizer::FacialRecognizer(int num_components, double threshold){
  model = cv::face::EigenFaceRecognizer::create(num_components, threshold);
}

FacialRecognizer::~FacialRecognizer(){
  delete model;
}

void FacialRecognizer::loadModel(const cv::FileStorage& fs){

}

void FacialRecognizer::saveModel(cv::FileStorage& fs){

}

void FacialRecognizer::trainModel(const cv::InputArray& src){
  // IN MAIN CODE, MUST UPDATE AND CREATE A vector<cv::Mat> TO PASS AS src
  // IN MAIN CODE, MUST UPDATE THE LABELS ASSOSCIATED WITH THE model
  model->cv::face::FaceRecognizer::train(src, labels);
}

void FacialRecognizer::identify(Image& src, int& label, double& confidence){
  cv::Mat predictThis;
  cv:cvtColor(src.asMat(), predictThis, CV_BGR2GRAY);  // Image changed to greyscale
  int predicted_label = -1;
  double predicted_confidence = 0.0;
  // Get the prediction and associated confidence from the model
  model->FaceRecognizer::predict(predictThis, predicted_label, predicted_confidence);
}
