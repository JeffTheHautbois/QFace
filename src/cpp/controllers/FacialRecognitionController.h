#ifndef SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
#define SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_
//#include <string>
//#include <vector>
//#include "opencv2/core.hpp"
#include "Image.h"
//#include <string>
//#include <vector>
//#include "lib/opencv_3.1.0/modules/face/include/opencv2/face.hpp"

using namespace cv;

/*
class FaceRecognizer : public Algorithm
{
public:
    //! virtual destructor
    virtual ~FaceRecognizer() {}

    // Trains a FaceRecognizer.
    virtual void train(InputArray src, InputArray labels) = 0;

    // Updates a FaceRecognizer.
    virtual void update(InputArrayOfArrays src, InputArray labels);

    // Gets a prediction from a FaceRecognizer.
    virtual int predict(InputArray src) const = 0;

    // Predicts the label and confidence for a given sample.
    virtual void predict(InputArray src, int &label, double &confidence) const = 0;

    // Serializes this object to a given filename.
    virtual void save(const String& filename) const;

    // Deserializes this object from a given filename.
    virtual void load(const FileStorage& fs);

    // Serializes this object to a given cv::FileStorage.
    virtual void save(FileStorage& fs) const = 0;

    // Deserializes this object from a given cv::FileStorage.
    virtual void load(const FileStorage& fs) = 0;

    // Sets additional string info for the label
    virtual void setLabelInfo(int label, const String& strInfo);

    // Gets string info by label
    virtual String getLabelInfo(int label);

    // Gets labels by string info
    virtual vector<int> getLabelsByString(const String& str);
};
*/

class FacialRecognizer {
public:
  // Facial Recognizer constructor
  FacialRecognizer();

  void loadDataSet();

  void loadModel(const cv::FileStorage& fs);

  void saveModel(cv::FileStorage& fs);

  void trainModel(cv::InputArrayOfArrays src, cv::InputArray labels);

  void cropAndSaveFaceTemporary(Image& inputImage);

  void identify(cv::InputArray src, int& label, double& confidence);

  void createFaceRecognizer(int num_components=0, double threshold=DBL_MAX);

};




#endif /* SRC_CPP_CONTROLLERS_FACIALRECOGNITIONCONTROLLER_H_ */
