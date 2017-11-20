#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "test/test.h"
#include "models/Database.h"
#include "controllers/FacialRecognitionController.h"

/*
 * Runs this code synchronously after the DB is initialized.
 */
void afterDbInit(emscripten::val) {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }
  FacialRecognizer face;
//  face.trainModel();
//  std::cout << "model trained" << std::endl;
//  face.saveModel();
  face.loadModel();
  std::cout << "model loaded from DB" << std::endl;
  std::cout << "It worked!" << "\n";
}

int main() {
  emscripten::val promise = Database::init();
  promise.call<void>("then", emscripten::val::module_property("main_afterDbInit"));
  return 0;
}


EMSCRIPTEN_BINDINGS(AfterDbInit) {
  emscripten::function("main_afterDbInit", &afterDbInit);
};
