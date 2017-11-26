#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "test/test.h"
#include "models/Database.h"

/*
 * Runs this code synchronously after the DB is initialized.
 */
void afterDbInit(emscripten::val) {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  std::cout << "Database successfully initialized, QFACE is ready to recognize!" << "\n";
}

int main() {
  emscripten::val promise = Database::init();
  promise.call<void>("then", emscripten::val::module_property("main_afterDbInit"));
  return 0;
}


EMSCRIPTEN_BINDINGS(AfterDbInit) {
  emscripten::function("main_afterDbInit", &afterDbInit);
};
