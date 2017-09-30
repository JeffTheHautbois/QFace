#include <emscripten.h>

#include "../controllers/stubController.h"

extern "C" {

int EMSCRIPTEN_KEEPALIVE stubViewFunction() {
    return 1 + stubControllerFunction();
}

}
