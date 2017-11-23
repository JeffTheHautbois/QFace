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
  // returns true if customer in Customer collection has same student number as studentId
  static bool isExistingCustomer(const int studentId);
  // overwrites customer in collection using studentId
  static void overwriteCustomer(const int studentId, const json & customer);
  // adds a new document to customer collection
  static void insertCustomer(const int studentId, const json & customer);
  // each user is associated to images by their student Id, the images collection
  // contains studentId/string pairs
  static void addImageToCustomer(const int studentId, const std::string & image);
  // returns json structure of document in customers collection but all of the fields are empty
  static json getCustomerStructure();
  // returns json structure representation of customer's document in the Customer collection
  static json getCustomer(int studentId);
  // using studentId, fills vector with image strings that correspond to user id in the Images collection
  static void getImagesOfCustomer(const int studentId,
                                  std::vector<std::string> & outVector,
                                  int numberOfResults);

  static void getAllStudentIdImagePairs(std::vector<int>* outIds, std::vector<std::string>* outImages);
 private:
  // Prevent this class from being instantiated
  CustomerModel() {}
};

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
