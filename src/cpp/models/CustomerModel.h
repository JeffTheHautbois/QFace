/*
 * CustomerModel.h
 *
 *  Created on: Nov 5, 2017
 *      Author: viraj
 */

#ifndef SRC_CPP_MODELS_CUSTOMERMODEL_H_
#define SRC_CPP_MODELS_CUSTOMERMODEL_H_

#include <string>
#include <emscripten/val.h>
#include "json.hpp"
using json = nlohmann::json;
using emscripten::val;

class CustomerModel {
 public:
  static bool hasBeenInit();
  static void saveCustomer(int);
  static void findCustomers();
  static json  getCustomerStructure();
  static json  getCustomer(int studentId);
  static void getAllCustomers();
  // Loads the database asynchronously. Returns a global promise
  // to allow stuff to allow things to happen after this is done.
  static val initDb();

  // Saves the database asynchronously. Returns a global promise
  // to allow stuff to allow things to happen after this is done.
  static val persist();

 private:
  // Prevent this class from being instantiated
  CustomerModel() {}
  static const std::string customerCollectionName;
  static const std::string dbPromiseName;
  static const std::string dbName;
  static const std::string isDbLoaded;
};

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
