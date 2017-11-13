/*
 * CustomerModel.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: viraj
 */

#include <emscripten.h>
#include <emscripten/val.h>
#include <iostream>
#include <vector>

#include "json.hpp"
#include "models/CustomerModel.h"
#include "models/Database.h"

using emscripten::val;
using json = nlohmann::json;


bool CustomerModel::isExistingCustomer(int studentId){
  if (!Database::hasBeenInit()) {
    return false;
  }
  // run find query using loki.js
  // if returned vector is not empty, return true (customer exists)
  val customers = Database::customersCollection();
  val selector = val::object();
  selector.set("studentId", studentId);
  val results = customers.call<val>("find", selector);
  unsigned int length = results["length"].as<unsigned int>();
  return (length > 0);
}

// accesses customer by student id key in customers collection and edits returned document
// using data in json user object
void CustomerModel::overwriteCustomer(const int studentId, const json &user) {
  if (!Database::hasBeenInit()) {
    return;
  }

  if (!isExistingCustomer(studentId)) {
    return; // Throw an exception.
  }

  val customers = Database::customersCollection();
  val query = val::object();
  query.set("studentId", studentId);

  val customer = customers.call<val>("findOne", query);
  // changes made to customer will persist in database
  customer.set("name", user["name"].get<std::string>());
  customer.set("age", user["age"].get<int>());
  customer.set("order", user["order"].get<std::string>());
}

// inserts one customer into the customer collection using data in json object
void CustomerModel::insertCustomer(const int studentId, const json &user) {
  if (!Database::hasBeenInit()) {
    return;
  }

  if (isExistingCustomer(studentId)) {
    return; // Throw an exception.
  }

  val customers = Database::customersCollection();

  val customer = val::object();
  customer.set("studentId", studentId);
  customer.set("name", user["name"].get<std::string>());
  customer.set("age", user["age"].get<int>());
  customer.set("order", user["order"].get<std::string>());
  customers.call<void>("insert", customer);
}

// just using string object for image instead of Image class for now
// also this assumes that the collection used for the customer images is called "images"
// Maybe we should pass the collection name as an argument in the future...
void CustomerModel::addImageToCustomer(const int studentId, const std::string &image) {
    // inserting new document into images collection
    // structure of document {studentId: 00000000, image: ""}
    if (!Database::hasBeenInit()) {
        return;
    }

    if (!isExistingCustomer(studentId)) {
      return; // should throw exception
    }

    val images = Database::imagesCollection();
    val document = val::object();
    document.set("studentId", studentId);
    document.set("image", image);
    images.call<val>("insert", document);
}

// In the SDD -> getImagesOfUser(std::string, std::vector<Image*>*, std::string<std::string>*, int)
// currently this function will add images by string to a vector
// I am assuming the int is for when we want a certain number of images
// if this argument is set to -1, return all images for student with studentId
void CustomerModel::getImagesOfCustomer(const int studentId,
                                        std::vector<std::string> &imageVecOut, int numImages) {
    if (!Database::hasBeenInit()) {
        return;
    }
    val images = Database::imagesCollection();
    val selector = val::object();
    selector.set("studentId", studentId);
    val results = images.call<val>("find", selector);
    int length = results["length"].as<int>();
    if (numImages < 0 || numImages > length) {
      for (int i = 0; i < length; ++i) {
        val image = results[i].as<val>();
        imageVecOut.push_back(image["image"].as<std::string>());
      }
    } else {
      for (int i = 0; i < numImages; ++i) {
        val image = results[i].as<val>();
        imageVecOut.push_back(image["image"].as<std::string>());
      }
    }
}

// This function replaces the original "getAllUsers" function.
// It should allow the retrieval of all studentId and image pairs in the images collection.
//
// For example, if the images collection contains:
// {"studentId": 1000, "image": "ASGxw.."}
// {"studentId": 1000, "image": "Vhx+s.."}
// {"studentId": 1010, "image": "OAnx.."}
// {"studentId": 1050, "image": "Waxv.."}
//
// The value of outIds should be
// [1000, 1000, 1010, 1050]
//
// The values of outImages should be
// ["ASGxw..", "Vhx+s..", "OAnx..", "Waxv.."]
void CustomerModel::getAllStudentIdImagePairs(std::vector<int>* outIds, std::vector<std::string>* outImages) {
   if (!Database::hasBeenInit()) {
        return;
    }
    val images = Database::imagesCollection();
    val results = images.call<val>("find");
    int length = results["length"].as<int>();
    for (int i = 0; i < length; ++i) {
      outIds->push_back(results[i]["studentId"].as<int>());
      outImages->push_back(results[i]["image"].as<std::string>());
    }
}