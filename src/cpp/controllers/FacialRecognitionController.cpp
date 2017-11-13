#include <iostream>
#include <string>
#include <emscripten.h>

#include "FacialRecognitionController.h"
//#include "lib/opencv_3.1.0/modules/face/include/opencv2/face.hpp"

using namespace std;
using namespace cv;

FacialRecognizer::FacialRecognizer(){
  //Ptr<FaceRecognizer> model = EigenFaceRecognizer::create();
  //Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
}

void FacialRecognizer::loadDataSet(){

}

void FacialRecognizer::loadModel(const cv::FileStorage& fs){

}

void FacialRecognizer::saveModel(cv::FileStorage& fs){

}

void FacialRecognizer::trainModel(cv::InputArrayOfArrays src, cv::InputArray labels){
 // model->train(images, labels)
}

void FacialRecognizer::cropAndSaveFaceTemporary(Image& inputImage){

}

void FacialRecognizer::identify(cv::InputArray src, int& label, double& confidence){
  // Do your initialization here (create the cv::FaceRecognizer model) ...
  // ...
  createFaceRecognizer(0,DBL_MAX);
 // Mat img = imread("person1/3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  // Some variables for the predicted label and associated confidence (e.g. distance):
  int predicted_label = -1;
  double predicted_confidence = 0.0;
  // Get the prediction and associated confidence from the model
  //FacialRecognizer::model->FaceRecognizer::predict(img, predicted_label, predicted_confidence);
}

void FacialRecognizer::createFaceRecognizer(int num_components, double threshold){

}

