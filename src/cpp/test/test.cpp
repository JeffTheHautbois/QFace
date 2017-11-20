#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

#include "test/test.h"
#include "test/TestRunner.h"
#include "models/TemporaryStorage.h"
#include "models/TrainedRecognizerModel.h"

void runTrainedRecognizerModelTests() {
  TestRunner tr("Runner for trained recognizer model");

  tr.addTest([]() {

   TrainedRecognizerModel::update("TEST1");
   std::string data2 = TrainedRecognizerModel::get();
   assert("TEST1" == data2 && "Saved string can be accessed.");

   TrainedRecognizerModel::update("one");
   TrainedRecognizerModel::update("two");
   TrainedRecognizerModel::update("three");
   std::string data3 = TrainedRecognizerModel::get();
   assert(data3 == "three" && "Multiple updates in a row, get returns last update.");

   TrainedRecognizerModel::update("");
   std::string data4 = TrainedRecognizerModel::get();
   assert(data4 == "" && "Update and get on empty string works.");

  }, "Tests is document in TrainedRecognizerModel can be updated and accessed.");
   tr.run();

}

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

void runTests() {
  
  runTrainedRecognizerModelTests();
  runTemporaryStorageTests();
}
