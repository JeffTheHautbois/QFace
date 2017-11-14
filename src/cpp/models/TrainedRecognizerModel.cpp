#include <emscripten.h>
#include <emscripten/val.h>
#include <iostream>
#include "Database.h"
#include "TrainedRecognizerModel.h"

void TrainedRecognizerModel::update(const std::string& serializedData) {
 if (!Database::hasBeenInit()) {
    return;
  }
  val collection = Database::trainedRecognizerCollection();
  collection.call<void>("removeDataOnly");
  val newData = val::object();
  newData.set("data", serializedData);
  collection.call<void>("insert", newData);
}

std::string TrainedRecognizerModel::get() {
 if (!Database::hasBeenInit()) {
    return "";
  }
  val data = Database::trainedRecognizerCollection();
  val result = data.call<val>("findOne");
  return result["data"].as<std::string>();
}