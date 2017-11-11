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
  static bool isExistingCustomer(const int studentId);
  static void overwriteCustomer(const int studentId, const json & customer);
  static void createNewCollection(const std::string &);
  static void addImageToCustomer(const int studentId, const std::string & image);
  static void getImagesOfCustomer(const int studentId,
                                  std::vector<std::string> & outVector,
                                  int numberOfResults);

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
  static const std::string imagesCollectionName;
  static const std::string dbPromiseName;
  static const std::string dbName;
  static const std::string isDbLoaded;
  static bool isValidStudentId(int);
};

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
