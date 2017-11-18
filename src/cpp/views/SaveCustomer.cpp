/*
 * SaveCustomer.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: ragulankodeeswaran
 */

#include "emscripten/bind.h"
#include "models/CustomerModel.h"
#include "models/TemporaryStorage.h"
#include "json.hpp"

using json = nlohmann::json;


void saveCustomer(int studentId, std::string customer) {
  json customerJSON = json::parse(customer);

  try {
    bool existingCustomer = CustomerModel::isExistingCustomer(studentId);
    if (existingCustomer) {
      CustomerModel::overwriteCustomer(studentId, customerJSON);
    } else {
      CustomerModel::insertCustomer(studentId, customerJSON);
    }
  } catch (CustomerException& e) {
    std::cout << e.what() << std::endl;
  }
  std::vector<std::string> images;
  TemporaryStorage::getImages(&images);
  for (unsigned int i = 0; i < images.size(); i++) {
    CustomerModel::addImageToCustomer(studentId, images[i]);
  }
  TemporaryStorage::clearStorage();
}

EMSCRIPTEN_BINDINGS(SaveCustomer) {
  emscripten::function("saveCustomer_saveCustomer", &saveCustomer);
}
