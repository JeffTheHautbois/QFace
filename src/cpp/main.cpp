#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "test/test.h"
#include "models/CustomerModel.h"


/*
 * Runs this code synchronously after the DB is initialized.
 */
void afterDbInit(val) {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  CustomerModel::saveCustomer(10000000);
  CustomerModel::saveCustomer(10000000);
  CustomerModel::saveCustomer(10186046);
  CustomerModel::findCustomers();

  std::cout << "It worked!" << "\n";
}

int main() {
  val promise = CustomerModel::initDb();
  promise.call<void>("then", val::module_property("main_afterDbInit"));

  return 0;
}


EMSCRIPTEN_BINDINGS(AfterDbInit) {
  emscripten::function("main_afterDbInit", &afterDbInit);
};
