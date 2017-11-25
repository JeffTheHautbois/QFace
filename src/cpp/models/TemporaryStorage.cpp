/*
 * TemporaryStorage.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: viraj
 */

#include <emscripten/val.h>
#include "TemporaryStorage.h"
#include "models/Database.h"

using emscripten::val;

// get images in collection and adds them to vector argument as strings
void TemporaryStorage::getImages(std::vector<std::string>* outVector) {
  val temporaryStorage = Database::temporaryStorageCollection();
  // find query with no filters - returns all images
  val allImages = temporaryStorage.call<val>("find");

  unsigned int length = allImages["length"].as<unsigned int>();
  for (unsigned int i = 0; i < length; ++i) {
    val image = allImages[i].as<val>();
    outVector->push_back(image["image"].as<std::string>());
  }
}

// adds image to temporary storage collection using insert 
void TemporaryStorage::addImage(std::string& image) {
  val temporaryStorage = Database::temporaryStorageCollection();
  val imageObject = val::object();
  imageObject.set("image", image);
  temporaryStorage.call<void>("insert", imageObject);
}

// clears temporary storage collection data, collection itself will persist
void TemporaryStorage::clearStorage() {
  val temporaryStorage = Database::temporaryStorageCollection();
  temporaryStorage.call<void>("removeDataOnly");
}
