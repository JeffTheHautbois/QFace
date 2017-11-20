#include <iostream>
#include <exception>
#include <string>
#include <emscripten.h>
#include <assert.h>
#include "opencv2/imgcodecs.hpp"
#include "FacialRecognitionController.h"
#include "models/TrainedRecognizerModel.h"
#include "models/CustomerModel.h"


FacialRecognizer::FacialRecognizer() :
model(cv::face::LBPHFaceRecognizer::create()), persistenceFiletype(".yaml") {}

// Read model from database as raw XML data and set current model to loaded model
void FacialRecognizer::loadModel(){
  try{
    cv::FileStorage fs;
    fs.open(TrainedRecognizerModel::get(), cv::FileStorage::READ + cv::FileStorage::MEMORY);
    assert(fs.isOpened());
    model->read(fs.root());
    fs.release();
  }
  catch(std::exception& e) {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      throw e;
  }
}

// Write model as raw XML data to a string and store in database
void FacialRecognizer::saveModel(){
  // Create a cv::FileStorage fs with xml formatting. Write to it in memory
  // (not disk) and then get the string representation to pass in to
  // the database update method
  cv::FileStorage fs(persistenceFiletype, cv::FileStorage::WRITE + cv::FileStorage::MEMORY);
  model->write(fs);
  TrainedRecognizerModel::update(fs.releaseAndGetString());
}

void FacialRecognizer::trainModel(){
  try {
    std::vector<int> labels;
    std::vector<std::string> images;
    CustomerModel::getAllStudentIdImagePairs(&labels, &images);
    std::vector<cv::Mat> sources;

    assert(labels.size() == images.size());
    for (unsigned int i = 0; i < labels.size(); i++) {
      Image tempb64(images[i]);
      cv::Mat tempGreyScale;
      cv::cvtColor(tempb64.asMat(), tempGreyScale, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
      sources.push_back(tempGreyScale);
    }

    model->train(sources, labels);
  } catch (std::exception& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    throw e;
  }
}

int FacialRecognizer::identify(Image& src, double* confidence){
  cv::Mat predictThis;
  cv::cvtColor(src.asMat(), predictThis, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
  int predictedLabel = -1;
  double predictedConfidence = -1;
  // Get the prediction and associated confidence from the model
  model->predict(predictThis, predictedLabel, predictedConfidence);
  *confidence = 100 - predictedConfidence;
  return predictedLabel;
}

void FacialRecognizer::updateModel(cv::InputArrayOfArrays& src){
  model->update(src, labels);
}
