#include <iostream>

#include "emscripten/bind.h"

#include "views/stubView.h"
#include "controllers/stubController.h"


std::string stubViewFunction() {
  return getCroppedDuckImage();
}

EMSCRIPTEN_BINDINGS(Turbo) {
    emscripten::function("stubViewFunction", &stubViewFunction);
}
