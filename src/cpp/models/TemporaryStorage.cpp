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

void TemporaryStorage::getImages(std::vector<std::string>* outVector) {
  val temporaryStorage = Database::temporaryStorageCollection();
  val allImages = temporaryStorage.call<val>("find");

  unsigned int length = allImages["length"].as<unsigned int>();
  for (unsigned int i = 0; i < length; ++i) {
    val image = allImages[i].as<val>();
    outVector->push_back(image["image"].as<std::string>());
  }
}

void TemporaryStorage::addImage(std::string& image) {
  val temporaryStorage = Database::temporaryStorageCollection();
  val imageObject = val::object();
  imageObject.set("image", image);
  temporaryStorage.call<void>("insert", imageObject);
}

void TemporaryStorage::clearStorage() {
  val temporaryStorage = Database::temporaryStorageCollection();
  temporaryStorage.call<void>("removeDataOnly");
}
