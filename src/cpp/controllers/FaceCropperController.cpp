#include <emscripten.h>
#include "FaceCropperController.h"
#include "models/TemporaryStorage.h"

using namespace std;
using namespace cv;

FaceCropper::FaceCropper() : face() {
  FaceCropper::loadCascadeClassifier("data/haarcascade_frontalface_default.xml"); // Load the cascade classfier from the filepath
}

void FaceCropper::loadCascadeClassifier(const std::string& filePath){
	face.load(filePath); // Load the xml file from the given file directory in the string
}

// Crops the image and saves it in temporary storage as a base64 String
void FaceCropper::cropFaceAndSaveInTemporaryStorage(Image& passedImage) {
  Mat inputImage = passedImage.asMat(); // The image as a matrix

  // Check if the image was loaded correctly
  if (inputImage.empty()) {
    string empty = "";
    throw FaceDetectionException("Error! Unable to load Image!");
  }

  Mat gray_img;
  vector<Rect> faces;
  cvtColor(inputImage, gray_img, CV_BGR2GRAY);  // Captured image modified with "RBG 2 GRAY" and stored in grey image
  equalizeHist(gray_img, gray_img);  // Normalize brightness and increase contrast if image

  // Detects objects of different sizes in the image, stored to faces (2nd paramater)
  face.detectMultiScale(gray_img, faces, 1.1, 10,
  CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING,
                        CvSize(0, 0), cvSize(300, 300));

  // Checks for the number of faces in the image
  if (faces.size() > 1) { // More than one face detected in the image
    throw FaceDetectionException("Error! Too many faces!");
  } else if (faces.size() == 0) { // No faces detected in the image
    throw FaceDetectionException("Error! No faces!");
  } else { // One face has been detected
    // The actual cropping occurs here.
    Rect faceROI = getFaceROI(gray_img);//(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
    Mat croppedFace = inputImage(faceROI); // The cropped face as a matrix
    Image returnImage(croppedFace); // Create an image object using the cropped face matrix

    std::string croppedImageBase64 = returnImage.asBase64();
    TemporaryStorage::addImage(croppedImageBase64); // Save cropped image as base64 string in temporary storage

  }
}

Rect FaceCropper::getFaceROI(Mat grayImg){
  vector<Rect> faces;
  Rect faceROI;
  face.detectMultiScale(grayImg, faces, 1.1, 10,
  CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING,
                        CvSize(0, 0), cvSize(300, 300));

  // Too many or no faces detected in the image
  if (faces.size() > 1 || faces.size() == 0)
    faceROI = Rect(0,0,0,0);
  else // One face has been detected
    faceROI = Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
  return faceROI;
}
