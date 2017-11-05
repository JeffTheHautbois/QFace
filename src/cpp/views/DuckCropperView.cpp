#include <iostream>
#include <string>

#include "emscripten/bind.h"

#include "controllers/DuckCropperController.h"
#include "views/DuckCropperView.h"
#include "models/CustomerModel.h"


std::string cropDuckImageToSquare(int length) {
  CustomerModel::saveCustomer("10186046");
  return croppedDuckImageAsByteString(length);
}

EMSCRIPTEN_BINDINGS(Turbo) {
    emscripten::function("duckCropper_cropDuckImageToSquare",
                         &cropDuckImageToSquare);
}
