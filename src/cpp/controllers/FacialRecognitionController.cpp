#include <iostream>
#include <string>
#include <emscripten.h>
#include "opencv2/face.hpp"
#include "FacialRecognitionController.h"

using namespace std;
using namespace cv;

/*
FacialRecognizer::FacialRecognizer(){
  model = cv::face::EigenFaceRecognizer::create(0,100);
}

FacialRecognizer::~FacialRecognizer(){
  delete model;
}

void FacialRecognizer::loadDataSet(){

}

void FacialRecognizer::loadModel(const cv::FileStorage& fs){

}

void FacialRecognizer::saveModel(cv::FileStorage& fs){

}

void FacialRecognizer::trainModel(const cv::InputArray& src){
  // IN MAIN CODE, MUST CREATE A vector<cv::Mat> TO PASS AS src
  model->cv::face::FaceRecognizer::train(src, labels);
}

void FacialRecognizer::identify(cv::InputArray src, int& label, double& confidence){
  // Mat img = imread("person1/3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  // Some variables for the predicted label and associated confidence (e.g. distance):
  int predicted_label = -1;
  double predicted_confidence = 0.0;
  // Get the prediction and associated confidence from the model
  //FacialRecognizer::model->FaceRecognizer::predict(img, predicted_label, predicted_confidence);
}

void FacialRecognizer::createFaceRecognizer(int num_components, double threshold){

}
*/
