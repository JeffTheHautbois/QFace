#ifndef SRC_CPP_MODELS_TEMPORARYSTORAGE_H_
#define SRC_CPP_MODELS_TEMPORARYSTORAGE_H_

#include <vector>
#include <string>

class TemporaryStorage {
 public:
  /*
   * Clears the temporary storage.
   */
  static void clearStorage();
  /*
   * Gets all images from the temporary storage and loads them into a vector.
   */
  static void getImages(std::vector<std::string>* outVector);
  /*
   * Adds an image to temporary storage.
   */
  static void addImage(std::string& image);
};

#endif /* SRC_CPP_MODELS_TEMPORARYSTORAGE_H_ */
