#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

#include "test/test.h"
#include "test/TestRunner.h"
#include "models/TemporaryStorage.h"
#include "models/Image.h"
#include "models/base64.h"
#include "controllers/FaceCropperController.h"
#include "opencv2/imgcodecs.hpp"


void runTemporaryStorageTests() {
  TestRunner tr("Runner for testing temporary storage");

  tr.addTest([]() {
    std::string image1 = "TEST1";
    TemporaryStorage::addImage(image1);

    std::string image2 = "TEST2";
    TemporaryStorage::addImage(image2);

    std::string image3 = "TEST2";
    TemporaryStorage::addImage(image3);

    std::vector<std::string> images;
    TemporaryStorage::getImages(&images);

    assert(images.size() == 3 && "Could not save images.");

    assert(images[0] == "TEST1" && "First image was not saved properly.");
    assert(images[1] == "TEST2" && "Second image was not saved properly.");
    assert(images[2] == "TEST2" && "Third image was not saved properly.");
  }, "Tests if images can be added to temporary storage.");

  tr.addTest([]() {
    TemporaryStorage::clearStorage();
    std::vector<std::string> images;
    TemporaryStorage::getImages(&images);
    assert(images.size() == 0 && "Could not delete images");

    TemporaryStorage::clearStorage();
    assert(images.size() == 0 && "Could not delete empty storage collection.");
  }, "Tests if images can be deleted");

  tr.run();
}

void imageTests(){
	TestRunner tr ("Runner for Image class testing");

	tr.addTest([](){
		cv::Mat mtx = cv::imread("./data/obama.bmp"); // Create a matrix from an image
		Image img = Image(mtx); // Create Image object using a matrix
		cv::Mat imageMtx = img.asMat();

		// Convert both matrices to grayscale
		cv::cvtColor(mtx, mtx, cv::COLOR_BGR2GRAY);
		cv::cvtColor(imageMtx, imageMtx, cv::COLOR_BGR2GRAY);

		cv::Mat diff;
		cv::compare(mtx, imageMtx, diff, cv::CMP_NE); // Compare the 2 matrices and store into diff
		int nz = cv::countNonZero(diff); // Count the number of non zeroes

		assert(nz == 0 && "Matrices are not equal");
	}, "Testing image matrix");
	tr.addTest([](){
		std::string encoded_string = "/9j/4AAQSkZJRgABAQEAeAB4AAD/2wBDAAIBAQIBAQICAgICAgICAwUDAwMDAwYEBAMFBwYHBwcGBwcICQsJCAgKCAcHCg0KCgsMDAwMBwkODw0MDgsMDAz/2wBDAQICAgMDAwYDAwYMCAcIDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAz/wAARCAAyADIDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREAAgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRChYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD5Pooor/RA+DCiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKAP/2Q==";
		Image img = Image(encoded_string); // Create an image object using encoded string
		cv::Mat imageMtx = img.asMat();

		cv::Mat mtx = cv::imread("./test_data/test_image.jpg"); // Create a matrix from an image file

		// Convert both matrices to grayscale
		cv::cvtColor(mtx, mtx, cv::COLOR_BGR2GRAY);
		cv::cvtColor(imageMtx, imageMtx, cv::COLOR_BGR2GRAY);

		cv::Mat diff;
		cv::compare(mtx, imageMtx, diff, cv::CMP_NE); // Compare the 2 matrices and store into diff
		int nz = cv::countNonZero(diff); // Count the number of non zeroes

		assert(nz == 0 && "Images are not the same");
	}, "Testing image base64 conversion to matrix");

	tr.addTest([](){
		cv::Mat mtx = cv::imread("./test_data/test_image.jpg"); // Create a matrix from an image file
		Image img1 = Image(mtx);
		std::vector<unsigned char> imageBytes1 = img1.asBytes();

		Image img = Image(imageBytes1);
		std::vector<unsigned char> imageBytes2 = img.asBytes();

		assert(std::memcmp(&imageBytes1, &imageBytes2, imageBytes1.size()) && "Bytes are not equal");
	}, "Testing image byte conversion");

	tr.run();
}

void runTests() {
	//runTemporaryStorageTests();
	imageTests();
}
