#include <iostream>
#include <string>
#include <emscripten.h>
#include "FaceCropperController.h"
#include "Image.h"

#include "models/MatModel.h"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

/*
 * Crops the duck image into a square. Does not modify the original image.
 */
std::string cropFaceImageAsByteString(Image& passedImage) {
  Mat inputImage = passedImage.asMat();
  //oadImageIntoMat("data/obama.bmp", &inputImage);

  if (inputImage.empty()) {
    cout << "Was not able to load image" << std::endl;
    string empty = "";
    return empty;
  }

  // This part should be handled by the Model.
  const string filePath = "data/haarcascade_frontalface_default.xml";
  cout << filePath << std::endl;
  CascadeClassifier face;
  face.load(filePath);

  Mat gray_img;
  vector<Rect> faces, eyes;
  cvtColor(inputImage, gray_img, CV_BGR2GRAY);  // captured image modified with "RBG 2 GRAY" and stored in grey image
  equalizeHist(gray_img, gray_img);  // normalize brightness and increase contrast if image

  // detects objects of different sizes in the image, stored to faces (2nd paramater)
  face.detectMultiScale(gray_img, faces, 1.1, 10,
  CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING,
                        CvSize(0, 0), cvSize(300, 300));

  if (faces.size() > 1) {
    cout << "Error! Too many faces!" << endl;
    return "";
  } else if (faces.size() == 0) {
    cout << "Error! No faces detected!" << endl;
    return "";
  } else {
    // The actual cropping occurs here.
    Rect faceROI(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
    Mat croppedFace = inputImage(faceROI);

    return convertMatToByteString(croppedFace);
  }

}
