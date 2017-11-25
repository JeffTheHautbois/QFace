/*
 * Common.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Ragulan
 */


#include <emscripten.h>
#include "emscripten/bind.h"
#include "controllers/FaceCropperController.h"
#include "controllers/FacialRecognitionController.h"
#include "models/Image.h"
#include "models/CustomerModel.h"
#include "models/TemporaryStorage.h"

namespace IdentifyCustomer {
  FaceCropper* cropper = nullptr;
  FacialRecognizer* recognizer = nullptr;

  /*
   * Returns false if there are no faces in the database.
   */
  bool init() {
    cropper = new FaceCropper();
    recognizer = new FacialRecognizer();
    TemporaryStorage::clearStorage();

    // Load an existing model if there is one. Otherwise,
    // train it with the data in the DB. If there is no data,
    // then return false.
    try {
      recognizer->loadModel();
    } catch(FaceDetectionException &e) {
      try {
        recognizer->trainModel();
      } catch (FaceDetectionException &e) {
        return false;
      }
    }

    return true;
  }

  void clean() {
    delete cropper;
    delete recognizer;
  }

  /*
   * Returns whether a face was detected and successfully stored.
   */
  bool saveFaceInTemporaryStorage(std::string imageString) {
    try {
      Image img(imageString);
      cropper->cropFaceAndSaveInTemporaryStorage(img);
      return true;
    } catch (FaceDetectionException& e) {
      std::cout << e.what() << std::endl;
      return false;
    }
  }

  /*
   * Returns studentId of matched face.
   */
  std::string identify(std::string imageString) {
    Image img(imageString);
    double confidence;
    int studentId = recognizer->identify(img, &confidence);

    return CustomerModel::getCustomer(studentId).dump();
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

  /*
   * Returns whether a face was detected and successfully stored.
   */
  void confirm(int studentId) {
    std::vector<std::string> imageStrings;
    TemporaryStorage::getImages(&imageStrings);

    std::vector<Image> images;
    std::vector<int> studentIds;

    for (std::string& image : imageStrings) {
      CustomerModel::addImageToCustomer(studentId, image);
      studentIds.push_back(studentId);
      images.push_back(Image(image));
    }

    recognizer->updateModel(images, studentIds);
    recognizer->saveModel();

    TemporaryStorage::clearStorage();
  }

  EMSCRIPTEN_BINDINGS(IdentifyCustomer) {
    emscripten::function("identifyCustomer_init", &init);
    emscripten::function("identifyCustomer_clean", &clean);
    emscripten::function("identifyCustomer_identify", &identify);
    emscripten::function("identifyCustomer_confirm", &confirm);
    emscripten::function("identifyCustomer_saveFaceInTemporaryStorage", &saveFaceInTemporaryStorage);
    emscripten::function("identifyCustomer_getCroppedFace", &getCroppedFace);
  }
}
