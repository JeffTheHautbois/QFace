#include <iostream>
#include <string>
#include <emscripten.h>

#include "FacialRecognitionController.h"
#include "lib/opencv_3.1.0/modules/face/include/opencv2/face.hpp"

using namespace std;
using namespace cv;

void FacialRecognizer::loadDataSet(){

}

void FacialRecognizer::loadModel(const cv::FileStorage& fs){

}

void FacialRecognizer::saveModel(cv::FileStorage& fs){

}

void FacialRecognizer::trainModel(cv::InputArrayOfArrays src, cv::InputArray labels){

}

void FacialRecognizer::cropAndSaveFaceTemporary(Image& inputImage){

}

void FacialRecognizer::identify(cv::InputArray src, int& label, double& confidence){

}

void FacialRecognizer::createFaceRecognizer(int num_components=0, double threshold=DBL_MAX){

}

