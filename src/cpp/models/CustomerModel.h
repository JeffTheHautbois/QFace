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

using emscripten::val;
using json = nlohmann::json;

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


  static bool isExistingCustomer(const int studentId);
  static void overwriteCustomer(const int studentId, const json & customer);
  static void insertCustomer(const int studentId, const json & customer);
  static void addImageToCustomer(const int studentId, const std::string & image);
  static void getImagesOfCustomer(const int studentId,
                                  std::vector<std::string> & outVector,
                                  int numberOfResults);
 private:
  // Prevent this class from being instantiated
  CustomerModel() {}
};

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
