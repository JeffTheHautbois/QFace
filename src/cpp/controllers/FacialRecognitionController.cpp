#include <iostream>
#include <string>
#include <emscripten.h>
#include "opencv2/face.hpp"
#include "FacialRecognitionController.h"
#include "models/TrainedRecognizerModel.h"

FacialRecognizer::FacialRecognizer(int radius, int neighbors, int grid_x, int grid_y, double threshold){
  model = cv::face::LBPHFaceRecognizer::create(radius, neighbors, grid_x, grid_y, threshold);
}

FacialRecognizer::~FacialRecognizer(){
  delete model;
}

// Read model from database as raw XML data and set current model to loaded model
void FacialRecognizer::loadModel(){
  cv::FileStorage fs;
  // get the string from the database, read to cv's fs in memory (not disk)
  // and open it to allow data be accessed
  fs.open(TrainedRecognizerModel::get(),cv::FileStorage::READ + cv::FileStorage::MEMORY);
  // cannot model->load(fs) in current OpenCV release. Must create a
  // cv::FileNode, created from the cv's fs, and then model "reads"
  // (loads) the saved state and replaces the current state with it
  cv::FileNode fn = fs;
  model->read(fn);
  fs.release();
}

// Write model as raw XML data to a string and store in database
void FacialRecognizer::saveModel(){
  // Create a cv::FileStorage fs with xml formatting. Write to it in memory
  // (not disk) and then get the string representation to pass in to
  // the database update method
  cv::FileStorage fs(".xml", cv::FileStorage::WRITE + cv::FileStorage::MEMORY);
  fs << model;
  TrainedRecognizerModel::update(fs.releaseAndGetString());
}

void FacialRecognizer::trainModel(const cv::InputArray& src){
  // IN MAIN CODE, MUST UPDATE AND CREATE A vector<cv::Mat> TO PASS AS src
  // IN MAIN CODE, MUST UPDATE THE LABELS ASSOSCIATED WITH THE model
  model->FaceRecognizer::train(src, labels);
}

void FacialRecognizer::identify(Image& src, int& label, double& confidence){
  cv::Mat predictThis;
  cv::cvtColor(src.asMat(), predictThis, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
  int predicted_label = -1;
  double predicted_confidence = 0.0;
  // Get the prediction and associated confidence from the model
  model->FaceRecognizer::predict(predictThis, predicted_label, predicted_confidence);
}

void FacialRecognizer::updateModel(cv::InputArrayOfArrays& src){
  model->FaceRecognizer::update(src, labels);
}
