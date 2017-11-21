#ifndef SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_
#define SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_

#include <string>
#include <emscripten/val.h>

// When the get method is called, the value of the data attribute
// should be assigned to a string pointer.
class TrainedRecognizerModel {
  public:
    // the single document in trained recognizer collection is updated to contain serializedData
    static void update(const std::string& serializedData);
    // returns string in single document
    static std::string get();
  private:
    TrainedRecognizerModel();
};

#endif /* SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_ */