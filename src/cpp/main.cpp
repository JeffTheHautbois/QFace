#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "test/test.h"
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
  CustomerModel::findCustomers();
  CustomerModel::isExistingUser(10186046);
  json j = {{"studentId",101},{"name", "HELLO"},{"age",21},{"order","turbo"}};
  CustomerModel::overWriteUser(j);
  //CustomerModel::createNewCollection("images");
  //CustomerModel::addImageToUser("100","AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
  //CustomerModel::addImageToUser("100",""); // shouldn't overwrite above document 
  //CustomerModel::addImageToUser("10091837","imagestring"); // shouldn't overwrite above document 
  std::vector<std::string> imagesForUser = {};
  CustomerModel::getImagesOfUser("100", imagesForUser, 1);
  int length = imagesForUser.size();
  for (int i = 0 ; i < length; i++) {
        std::cout << imagesForUser[i] <<"\n"; 
  }
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
