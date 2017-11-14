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
  // couldn't get this to work when passing ptr to get
  //*outString = (result["data"].as<std::string>());
}






  // tried to keep outString as string but result["data"] =='emscripten::val'
  // pointer argument can then change val returned, cant convert to string and then edit
  // changed param to val because its easy to convert to string,
  // and update function can use this function to update document -> doesnt work bc binding errror
  // last resort, return string and redo this code in update... 