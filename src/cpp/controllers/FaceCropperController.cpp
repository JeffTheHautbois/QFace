#include <emscripten.h>
#include "FaceCropperController.h"

using namespace std;
using namespace cv;

FaceCropper::FaceCropper() : face() {
  FaceCropper::loadCascadeClassifier("data/haarcascade_frontalface_default.xml"); // Load the cascade classfier from the filepath
}

void FaceCropper::loadCascadeClassifier(const std::string& filePath){
	face.load(filePath); // Load the xml file from the given file directory in the string
}

// Crops the image and saves it in temporary storage as a base64 String
std::string FaceCropper::cropFaceAndSaveInTemporaryStorage(Image& passedImage) {
  Mat inputImage = passedImage.asMat(); // The image as a matrix

  // Check if the image was loaded correctly
  if (inputImage.empty()) {
    cout << "Was not able to load image" << std::endl;
    string empty = "";
    return empty;
  }

  Mat gray_img;
  vector<Rect> faces, eyes;
  cvtColor(inputImage, gray_img, CV_BGR2GRAY);  // Captured image modified with "RBG 2 GRAY" and stored in grey image
  equalizeHist(gray_img, gray_img);  // Normalize brightness and increase contrast if image

  // Detects objects of different sizes in the image, stored to faces (2nd paramater)
  face.detectMultiScale(gray_img, faces, 1.1, 10,
  CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING,
                        CvSize(0, 0), cvSize(300, 300));

  // Checks for the number of faces in the image
  if (faces.size() > 1) { // More than one face detected in the image
    throw FaceDetectionException("Error! Too many faces!");
    return "";
  } else if (faces.size() == 0) { // No faces detected in the image
    throw FaceDetectionException("Error! No faces!");
    return "";
  } else { // One face has been detected
    // The actual cropping occurs here.
    Rect faceROI(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
    Mat croppedFace = inputImage(faceROI); // The cropped face as a matrix
    Image returnImage(croppedFace); // Create an image object using the cropped face matrix

    return returnImage.asBase64(); // Return the image object as a Base64 String
  }

}
