#include <emscripten.h>

#include "views/stubView.h"
#include "controllers/stubController.h"

extern "C" {

int EMSCRIPTEN_KEEPALIVE stubViewFunction() {
  return 1 + stubControllerFunction();
}

}
