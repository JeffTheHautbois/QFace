/*
 * Index.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: viraj
 */
#include "controllers/FacialRecognitionController.h"

#include "emscripten/bind.h"
#include <vector>


namespace Index {
  void retrainModel() {
    FacialRecognizer fc;
    fc.trainModel();
    fc.saveModel();
  }

  EMSCRIPTEN_BINDINGS(Index) {
    emscripten::function("index_retrainModel", &retrainModel);
  }

}



