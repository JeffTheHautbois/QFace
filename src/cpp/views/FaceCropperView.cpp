#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/FaceCropperController.h"
#include "views/FaceCropperView.h"
#include "opencv2/imgcodecs.hpp"
#include "models/TemporaryStorage.h"

void detectCropFace() {
  TemporaryStorage::clearStorage();
  Image passThisImage = Image(cv::imread("./data/obama.bmp"));
  FaceCropper fcc;
	fcc.cropFaceAndSaveInTemporaryStorage(passThisImage); // Crop the face
}

EMSCRIPTEN_BINDINGS(Turbo) {
	emscripten::function("faceCropper_detectCropFace", &detectCropFace);
}
