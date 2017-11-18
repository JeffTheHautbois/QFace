#include <iostream>
#include <string>
#include <emscripten.h>
#include "opencv2/face.hpp"
#include "FacialRecognitionController.h"

FacialRecognizer::FacialRecognizer(int radius, int neighbors, int grid_x, int grid_y, double threshold){
  model = cv::face::LBPHFaceRecognizer::create(radius, neighbors, grid_x, grid_y, threshold);
}

FacialRecognizer::~FacialRecognizer(){
  delete model;
}

// Read model from database as raw XML data and set current model to  loaded model
void FacialRecognizer::loadModel(){
  std::string xmlRaw;
  cv::FileStorage fs;
  fs.open(xmlRaw,cv::FileStorage::READ|cv::FileStorage::MEMORY);
  model->load(fs);
  fs.release();
}

// Write model as raw XML data to a string and store in database
void FacialRecognizer::saveModel(){
  std::string xmlRaw;
  cv::FileStorage fs;
  fs.open(xmlRaw,cv::FileStorage::WRITE|cv::FileStorage::MEMORY);
  model->save(fs);
  fs.release();
}

void FacialRecognizer::trainModel(const cv::InputArray& src){
  // IN MAIN CODE, MUST UPDATE AND CREATE A vector<cv::Mat> TO PASS AS src
  // IN MAIN CODE, MUST UPDATE THE LABELS ASSOSCIATED WITH THE model
  model->FaceRecognizer::train(src, labels);
}

void FacialRecognizer::identify(Image& src, int& label, double& confidence){
  cv::Mat predictThis;
  cv::cvtColor(src.asMat(), predictThis, CV_BGR2GRAY);  // Image changed to greyscale
  int predicted_label = -1;
  double predicted_confidence = 0.0;
  // Get the prediction and associated confidence from the model
  model->FaceRecognizer::predict(predictThis, predicted_label, predicted_confidence);
}

void FacialRecognizer::updateModel(cv::InputArrayOfArrays& src){
  model->FaceRecognizer::update(src, labels);
}
