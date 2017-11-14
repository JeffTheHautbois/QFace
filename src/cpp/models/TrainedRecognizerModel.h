#ifndef SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_
#define SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_

#include <string>
#include <emscripten/val.h>

// The controller team requires persistent storage
// of a serialized trained cv::FaceRecognizer.
// To solve this, a new collection called TrainedRecognizer
// should be implemented. This collection is actually very
// simple - there will only ever be a single entry in the
// collection, and that specific entry is what is returned
// or modified. The value of that entry should be specified
// by the controller.
//
// Example entry:
// {"data": <some string that the controller passes in>.
//
// When the update(std::string& serializedData) method is called, 
// the single entry that exists should have it's data attribute 
// modified to match serializedData.
//
// When the get method is called, the value of the data attribute
// should be assigned to a string pointer.
class TrainedRecognizerModel {
  public:
    static void update(const std::string& serializedData);
    static std::string get();
  private:
    TrainedRecognizerModel();
};

#endif /* SRC_CPP_MODELS_TRAINEDRECOGNIZERMODEL_H_ */