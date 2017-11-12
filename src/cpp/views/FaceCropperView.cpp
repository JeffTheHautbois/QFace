#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/FaceCropperController.h"
#include "views/FaceCropperView.h"

std::string detectCropFace(Image& passThisImage) {
	cv::CascadeClassifier face; // Create new Cascade Classifier object
	const std::string filePath = "data/haarcascade_frontalface_default.xml"; // Path of XML file
	face = loadCascadeClassifier(filePath); // Load the CascadeClassifier object into face
	return cropFaceImageAsByteString(passThisImage, face); // Crop the face
}

EMSCRIPTEN_BINDINGS(Turbo) {
  emscripten::function("faceCropper_detectCropFace", &detectCropFace);
}
