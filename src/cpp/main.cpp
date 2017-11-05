#include <iostream>

#include "test/test.h"
#include "models/CustomerModel.h"


int main() {
  bool inTestEnv = false;
  if (inTestEnv) {
      runTests();
  }

  CustomerModel::initDb();
  CustomerModel::saveCustomer("10186042");

  std::cout << "It worked!" << "\n";
  return 0;
}
