#include <emscripten/bind.h>

#include "views/stubView.h"
#include "controllers/stubController.h"

using emscripten::function;

int stubViewFunction() {
  return 1 + stubControllerFunction();
}

EMSCRIPTEN_BINDINGS(Turbo) {
    function("stubViewFunction", &stubViewFunction);
}
