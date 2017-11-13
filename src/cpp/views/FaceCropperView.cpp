#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/FaceCropperController.h"
#include "views/FaceCropperView.h"
#include "opencv2/imgcodecs.hpp"

std::string detectCropFace() {
  Image passThisImage = Image(cv::imread("./data/obama.bmp"));
  FaceCropper fcc;
	return fcc.cropFaceAndSaveInTemporaryStorage(passThisImage); // Crop the face
}

EMSCRIPTEN_BINDINGS(Turbo) {
	emscripten::function("faceCropper_detectCropFace", &detectCropFace);
}
