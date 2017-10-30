#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/DuckCropperController.h"
#include "views/DuckCropperView.h"


std::string cropDuckImageToSquare(int length) {
  return croppedDuckImageAsByteString(length);
}

EMSCRIPTEN_BINDINGS(Turbo) {
    emscripten::function("duckCropper_cropDuckImageToSquare",
                         &cropDuckImageToSquare);
}
