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

  unsigned int length = results["length"].as<unsigned int>();
  for(unsigned int i = 0; i < length; ++i) {
    val customer = results[i].as<val>();
    std::cout << customer["name"].as<std::string>() << std::endl;
    std::cout << customer["studentId"].as<int>() << std::endl;
    std::cout << customer["age"].as<int>() << std::endl;
  }

}


// Sturcture for the json files
json  CustomerModel::getCustomerStructure() {
	//Check for how it looks on the front end
	json structure = {
		{ "name", "" },
		{ "studentId", "" },
		{ "age", "" },
		{ "order", "" }
	};
	return structure;
}


// Check if customer exisits, get customer info, write it into json and then return
json  CustomerModel::getCustomer(int studentId) {

	if (!CustomerModel::isExistingCustomer(studentId)){
	return CustomerModel::getCustomerStructure(); 
	}
	

	val window = val::global("window");
	val customers = window[dbName].call<val>("getCollection", customerCollectionName);
	val selector = val::object();
	selector.set("studentId", studentId);
	val results = customers.call<val>("findOne", selector);
	
	val customer = results.as<val>();

	json jsonCustomer = {
		{ "name", customer["name"].as<std::string>() },
		{ "studentId", customer["studentId"].as<int>() },
		{ "age", customer["age"].as<int>() },
		{ "order", customer["order"].as<string>()}
	};
	return jsonCustomer;


// In the SDD -> getImagesOfUser(std::string, std::vector<Image*>*, std::string<std::string>*, int)
// currently this function will add images by string to a vector
// I am assuming the int is for when we want a certain number of images
// if this argument is set to -1, return all images for student with studentId
void CustomerModel::getImagesOfCustomer(const int studentId,
                                        std::vector<std::string> &imageVecOut, int numImages) {
    if (!Database::hasBeenInit()) {
        return;
    }
    val window = val::global("window");
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

// Return the studentID for all customers in the 'customers' collection
void CustomerModel::getAllCustomers() {

	val window = val::global("window");
	val customers = window[dbName].call<val>("getCollection", customerCollectionName);
	val results = customers.call<val>("find");

	unsigned int length = results["length"].as<unsigned int>();

	// Check that there are customers in the collection
	if (length == 0) {
		std::cout << No customers saved. << std::endl;
	}

	for (unsigned int i = 0; i < length; ++i) {
		val customer = results[i].as<val>();
		std::cout << customer["studentId"].as<int>() << std::endl;
	}

}

