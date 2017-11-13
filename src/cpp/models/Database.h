/*
 * Database.h
 *
 *  Created on: Nov 11, 2017
 *      Author: viraj
 */

#ifndef SRC_CPP_MODELS_DATABASE_H_
#define SRC_CPP_MODELS_DATABASE_H_

#include <string>
#include <emscripten/val.h>

using emscripten::val;

class Database {
 public:
  // Loads the database asynchronously. Returns a global promise
  // to allow stuff to allow things to happen after this is done.
  static val init();

  static bool hasBeenInit();

  // Saves the database asynchronously. Returns a global promise
  // to allow stuff to allow things to happen after this is done.
  static val persist();

  static val customersCollection();
  static val imagesCollection();
  static val temporaryStorageCollection();
 private:
  static const std::string temporaryStorageCollectionName;
  static const std::string customerCollectionName;
  static const std::string imagesCollectionName;
  static const std::string dbPromiseName;
  static const std::string dbName;
  static const std::string isDbLoaded;
};

#endif /* SRC_CPP_MODELS_DATABASE_H_ */
