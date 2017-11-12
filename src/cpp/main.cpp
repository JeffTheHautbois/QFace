#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "test/test.h"
#include "models/Database.h"
#include "models/CustomerModel.h"
#include "json.hpp"
using json = nlohmann::json;

/*
 * Runs this code synchronously after the DB is initialized.
 */
void afterDbInit(val) {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  std::cout << "It worked!" << "\n";
}

int main() {
  val promise = Database::init();
  promise.call<void>("then", val::module_property("main_afterDbInit"));
  return 0;
}


EMSCRIPTEN_BINDINGS(AfterDbInit) {
  emscripten::function("main_afterDbInit", &afterDbInit);
};
