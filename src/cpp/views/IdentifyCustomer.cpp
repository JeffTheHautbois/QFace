/*
 * Common.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Ragulan
 */


#include "emscripten/bind.h"
#include "controllers/FaceCropperController.h"
#include "models/TemporaryStorage.h"

namespace IdentifyCustomer {
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
  std::string getCroppedFace() {
    std::vector<std::string> images;
    TemporaryStorage::getImages(&images);
    if (images.size() > 0) {
      return images[0];
    }
    return "";
  }

  EMSCRIPTEN_BINDINGS(IdentifyCustomer) {
    emscripten::function("identifyCustomer_init", &init);
    emscripten::function("identifyCustomer_clean", &clean);
    emscripten::function("identifyCustomer_saveFaceInTemporaryStorage", &saveFaceInTemporaryStorage);
    emscripten::function("identifyCustomer_getCroppedFace", &getCroppedFace);
  }
}
