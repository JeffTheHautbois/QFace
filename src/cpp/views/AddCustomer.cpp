#include "emscripten/bind.h"
#include "controllers/FaceCropperController.h"
#include "models/TemporaryStorage.h"

FaceCropper* fc = nullptr;

void init() {
  fc = new FaceCropper();
  TemporaryStorage::clearStorage();
}

void clean() {
  delete fc;
}

/*
 * Returns whether a face was detected and successfully stored.
 */
bool saveFaceInTemporaryStorage(std::string imageString) {
  try {
    Image img(imageString);
    fc->cropFaceAndSaveInTemporaryStorage(img);
    return true;
  } catch (FaceDetectionException& e) {
    std::cout << e.what() << std::endl;
    return false;
  }
}

/*
 * Returns whether a face was detected and successfully stored.
 */
std::string mostRecentDetectedFace() {
  std::vector<std::string> images;
  TemporaryStorage::getImages(&images);
  if (images.size() > 0) {
    return images[images.size() - 1];
  }
  return "";
}

EMSCRIPTEN_BINDINGS(AddCustomer) {
  emscripten::function("addCustomer_init", &init);
  emscripten::function("addCustomer_clean", &clean);
  emscripten::function("addCustomer_saveFaceInTemporaryStorage", &saveFaceInTemporaryStorage);
  emscripten::function("addCustomer_mostRecentDetectedFace", &mostRecentDetectedFace);
}
