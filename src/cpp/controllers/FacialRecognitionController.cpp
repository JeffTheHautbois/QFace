#include <iostream>
#include <string>
#include <emscripten.h>
#include <assert.h>
#include "opencv2/imgcodecs.hpp"
#include "FacialRecognitionController.h"
#include "models/TrainedRecognizerModel.h"
#include "models/CustomerModel.h"

// Default Constructor
FacialRecognizer::FacialRecognizer() : model(cv::face::LBPHFaceRecognizer::create()),
      persistenceFiletype(".yaml") {}

// Read model from database as raw YAML data and set current model to loaded model
void FacialRecognizer::loadModel() {
  try {
    // Create and open a cv::FileStorage object, to read the model from the persistent
    // storage. The string parameter is a "filename" which is read from MEMORY not the disk
    cv::FileStorage fs;
    fs.open(TrainedRecognizerModel::get(), cv::FileStorage::READ + cv::FileStorage::MEMORY);
    assert(fs.isOpened()); // fs must be opened
    model->read(fs.root()); // read uses cv::FileNode (fn), so fetch root fn from fs
    fs.release(); // Close fs to avoid errors
  } catch (cv::Exception& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    throw e;
  }
}

// Write model as raw YAML data to a string and store in database
void FacialRecognizer::saveModel() {
  // Create a cv::FileStorage fs with YAML formatting. Write to it in MEMORY
  // and then get the string representation to pass in to the persistent storage
  cv::FileStorage fs(persistenceFiletype, cv::FileStorage::WRITE + cv::FileStorage::MEMORY);
  model->write(fs); // saves trained model to fs
  // releaseAndGetString() returns a string with raw YAML data and closes the fs
  TrainedRecognizerModel::update(fs.releaseAndGetString());
}

// Train the model based on all images and student ID pairs
void FacialRecognizer::trainModel() {
  try {
    std::vector<int> labels;
    std::vector<std::string> images;
    std::vector<cv::Mat> sources;
    // Fetch all student ID and image pairs
    CustomerModel::getAllStudentIdImagePairs(&labels, &images);

    // Image and label vectors must be of equal length
    assert(labels.size() == images.size());
    for (unsigned int i = 0; i < labels.size(); i++) {
      // Create temporary Image object from base64String and then
      // convert to cv::Mat and push a greyscale representation of
      // the converted value to the source vector for training
      Image tempb64(images[i]);
      cv::Mat tempGreyScale;
      cv::cvtColor(tempb64.asMat(), tempGreyScale, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
      sources.push_back(tempGreyScale);
    }
    model->train(sources, labels);
  } catch (cv::Exception& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    throw e;
  }
}

// Identify a customer in the database from a passed Image. confidence parameter
// is a pointer to a double, which represents the "distance from a closest match".
// i.e 0 is a perfect match, 100 is better than 200, etc.
int FacialRecognizer::identify(Image& src, double* confidence) {
  // Create a greyscale cv::Mat representation of the passed src Image
  // so the predict() can attempt to identify a customer.
  cv::Mat predictThis;
  cv::cvtColor(src.asMat(), predictThis, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
  int predictedLabel = -1;
  double predictedConfidence = -1;
  // Get the prediction and associated confidence from the model
  model->predict(predictThis, predictedLabel, predictedConfidence);
  *confidence = 100 - predictedConfidence; // Attempt at a percentage representation
  return predictedLabel;
}

// Update "trains" the current model, but only does a limited "training". i.e
// existing images and labels in the model remain and are trained, only new
// images and labels are "trained" and then concatenated to the existing learned images
void FacialRecognizer::updateModel(std::vector<Image>& newImages, std::vector<int>& newLabels) {
  std::vector<cv::Mat> newImageMats;
  assert(newLabels.size() == newImages.size());
  // Image and label vectors must be of equal length
  for (unsigned int i = 0; i < newLabels.size(); i++) {
    // Similar to training. Images must be greyscale in order to update
    // (concatenate to) the current model
    cv::Mat tempGreyScale;
    cv::cvtColor(newImages[i].asMat(), tempGreyScale, cv::COLOR_RGB2GRAY);  // Image changed to greyscale
    newImageMats.push_back(tempGreyScale);
  }
  model->update(newImageMats, newLabels);
}
