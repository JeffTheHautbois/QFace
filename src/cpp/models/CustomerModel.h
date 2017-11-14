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

// An exception that is thrown if there are errors with the customer infomation
class CustomerException {
public:
  CustomerException(const std::string&);
  std::string& what();
private:
  std::string message;
};

class CustomerModel {
 public:
  static bool isExistingCustomer(const int studentId);
  static void overwriteCustomer(const int studentId, const json & customer);
  static void insertCustomer(const int studentId, const json & customer);
  static void addImageToCustomer(const int studentId, const std::string & image);
  static json getCustomerStructure();
  static json getCustomer(int studentId);
  static void getImagesOfCustomer(const int studentId,
                                  std::vector<std::string> & outVector,
                                  int numberOfResults);

  static void getAllStudentIdImagePairs(std::vector<int>* outIds, std::vector<std::string>* outImages);
 private:
  // Prevent this class from being instantiated
  CustomerModel() {}
};

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
