/*
 * TemporaryStorage.h
 *
 *  Created on: Nov 11, 2017
 *      Author: viraj
 */

#ifndef SRC_CPP_MODELS_TEMPORARYSTORAGE_H_
#define SRC_CPP_MODELS_TEMPORARYSTORAGE_H_

#include <vector>
#include <string>

class TemporaryStorage {
 public:
  static void clearStorage();
  static void getImages(std::vector<std::string>* outVector);
  static void addImage(std::string& image);
};

#endif /* SRC_CPP_MODELS_TEMPORARYSTORAGE_H_ */
