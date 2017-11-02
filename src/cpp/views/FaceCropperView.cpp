#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/FaceCropperController.h"
#include "views/FaceCropperView.h"

std::string detectCropFace() {
  return cropFaceImageAsByteString();
}

EMSCRIPTEN_BINDINGS(Turbo) {
  emscripten::function("faceCropper_detectCropFace", &detectCropFace);
}
