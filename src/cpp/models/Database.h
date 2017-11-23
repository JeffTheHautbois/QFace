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

// An exception that is thrown if the database doesn't exist 
class DatabaseException {
public:
  DatabaseException(const std::string&);
  std::string& what();
private:
  std::string message;
};

class Database {
 public:
  // Loads the database asynchronously. Returns a global promise
  static val init();
  // returns true if database is successfully initialized
  static bool hasBeenInit();
  // Saves the database asynchronously. Returns a global promise
  // to allow stuff to allow things to happen after this is done.
  static val persist();
  // returns customer collection object from db
  static val customersCollection();
  // returns images collection object from db
  static val imagesCollection();
  // returns temporary storage collection object from db
  static val temporaryStorageCollection();
  // returns trained recognizer collection object from db
  static val trainedRecognizerCollection();
 private:
  static const std::string temporaryStorageCollectionName;
  static const std::string customerCollectionName;
  static const std::string imagesCollectionName;
  static const std::string dbPromiseName;
  static const std::string dbName;
  static const std::string isDbLoaded;
  static const std::string trainedRecognizerCollectionName;
};

#endif /* SRC_CPP_MODELS_DATABASE_H_ */
