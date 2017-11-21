#include <emscripten.h>
#include <emscripten/val.h>
#include <iostream>
#include "Database.h"
#include "TrainedRecognizerModel.h"

// changes trained recognizer collection data document to match serializedData
void TrainedRecognizerModel::update(const std::string& serializedData) {
 if (!Database::hasBeenInit()) {
    return;
  }
  val collection = Database::trainedRecognizerCollection();
  // removes data from trained recognizer collection, the collection itself persists after this call
  collection.call<void>("removeDataOnly");
  val newData = val::object();
  newData.set("data", serializedData);
  // add new document to trained recognizer collection
  collection.call<void>("insert", newData);
}

// Example entry:
// {"data": <some string that the controller passes in>.
std::string TrainedRecognizerModel::get() {
 if (!Database::hasBeenInit()) {
    return ""; 
  }
  val data = Database::trainedRecognizerCollection();
  val result = data.call<val>("findOne");
  return result["data"].as<std::string>();
}