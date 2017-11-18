#include "models/TemporaryStorage.h"
#include "models/CustomerModel.h"
#include "models/Database.h"

#include <emscripten/val.h>
#include "emscripten/bind.h"
#include <vector>

using emscripten::val;

void clearTemporaryStorage() {
  TemporaryStorage::clearStorage();
}

val getImagesInTemporaryStorage() {
  std::vector<std::string> images;
  TemporaryStorage::getImages(&images);
  val jsImages = val::array();
  for (unsigned int i = 0; i < images.size(); i++) {
    jsImages.call<void>("push", images[i]);
  }
  return jsImages;
}

std::string getCustomer(int studentId) {
  bool existingCustomer = CustomerModel::isExistingCustomer(studentId);

  json customer;
  if (existingCustomer) {
    customer = CustomerModel::getCustomer(studentId);
  } else {
    customer = CustomerModel::getCustomerStructure();
  }
  return customer.dump();
}

val getImagesOfUser(int studentId, int numberOfImages) {
  std::vector<std::string> images;
  CustomerModel::getImagesOfCustomer(studentId, images, numberOfImages);
  val jsImages = val::array();
  for (unsigned int i = 0; i < images.size(); i++) {
    jsImages.call<void>("push", images[i]);
  }
  return jsImages;
}

emscripten::val persist() {
  return Database::persist();
}

EMSCRIPTEN_BINDINGS(Common) {
  emscripten::function("persist", &persist);
  emscripten::function("clearTemporaryStorage", &clearTemporaryStorage);
  emscripten::function("getImagesInTemporaryStorage", &getImagesInTemporaryStorage);
  emscripten::function("getCustomer", &getCustomer);
  emscripten::function("getImagesOfUser", &getImagesOfUser);


}
