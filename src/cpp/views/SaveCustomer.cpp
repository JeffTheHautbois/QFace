/*
 * SaveCustomer.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: ragulankodeeswaran
 */

#include "emscripten/bind.h"
#include "models/CustomerModel.h"
#include "models/TemporaryStorage.h"
#include "controllers/FacialRecognitionController.h"
#include "controllers/FaceCropperController.h"
#include "json.hpp"

namespace SaveCustomer {
  using json = nlohmann::json;


  void saveCustomer(int studentId, std::string customer) {
    json customerJSON = json::parse(customer);

    try {
      bool existingCustomer = CustomerModel::isExistingCustomer(studentId);
      if (existingCustomer) {
        CustomerModel::overwriteCustomer(studentId, customerJSON);
      } else {
        CustomerModel::insertCustomer(studentId, customerJSON);
      }
    } catch (CustomerException& e) {
      std::cout << e.what() << std::endl;
    }
    std::vector<std::string> imageString;
    TemporaryStorage::getImages(&imageString);
    for (unsigned int i = 0; i < imageString.size(); i++) {
      CustomerModel::addImageToCustomer(studentId, imageString[i]);
    }

    FacialRecognizer fc;
    try {
      fc.loadModel();

      std::vector<Image> images;
      std::vector<int> studentIds;

      for (std::string& image : imageString) {
        studentIds.push_back(studentId);
        images.push_back(Image(image));
      }

      fc.updateModel(images, studentIds);

    } catch (FaceDetectionException &e) {
      // If there is no previously existing model, train with
      // the data just added to to the customer collection.
      fc.trainModel();
    }

    fc.saveModel();
    TemporaryStorage::clearStorage();
  }

  EMSCRIPTEN_BINDINGS(SaveCustomer) {
    emscripten::function("saveCustomer_saveCustomer", &saveCustomer);
  }
}
