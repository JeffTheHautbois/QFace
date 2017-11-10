/*
 * CustomerModel.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: viraj
 */

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <iostream>
#include <vector>

#include "json.hpp"
#include "models/CustomerModel.h"

using emscripten::val;
using json = nlohmann::json;

const std::string CustomerModel::customerCollectionName = "customers";
const std::string CustomerModel::imagesCollectionName = "images";
const std::string CustomerModel::dbPromiseName = "dbPromise";
const std::string CustomerModel::dbName = "db";
const std::string CustomerModel::isDbLoaded = "isDbLoaded";

val CustomerModel::initDb() {
  val window = val::global("window");

  // Create a global promise object. This will allow other parts of the
  // code to handle async saves.
  val dbPromise = val::global("Promise").call<val>("resolve");
  val::global("window").set(dbPromiseName, dbPromise);
  window.set(isDbLoaded, false);

  EM_ASM({
    let customerCollectionName = UTF8ToString($0);
    let dbName = UTF8ToString($1);
    let dbPromiseName = UTF8ToString($2);
    let isLoaded = UTF8ToString($3);

    // Create a promise that is only resolved once the DB is loaded.
    // This can allow other parts of the code from modifying/reading
    // the DB before it is loaded.
    window[dbPromiseName] = window[dbPromiseName].then(function() {

      // LokiJS does not support promises by default. Since they use
      // callbacks, we need to wrap the constructor into the promise
      // notation.
      return new Promise((resolve, reject) => {

        // Here, the DB collections are initialized. Add more or less
        // as needed. This should theoretically be the only thing in
        // this mess of JS/C++ that needs to be changed.
        let databaseInitialize = function () {
          if (!window.db.getCollection(customerCollectionName)) {
            window.db.addCollection(customerCollectionName, {
              indices: ['studentId']
            });
          }
          console.log('Db has been loaded.');
          window[isLoaded] = true;
          return resolve();
        };

        // LokiJS constructor arguments.
        let idbAdapter = new LokiIndexedAdapter();
        let lokiArgs = {};
        lokiArgs.adapter = idbAdapter;
        lokiArgs.autoload = true;
        lokiArgs.autosave = true;
        lokiArgs.autoSaveInterval = 1000; // Save every second
        lokiArgs.autoloadCallback = databaseInitialize;

        // Add the db to the global window object.
        window[dbName] = new loki('Turbo.db', lokiArgs);
      });
    });
  },
  customerCollectionName.c_str(),
  dbName.c_str(),
  dbPromiseName.c_str(),
  isDbLoaded.c_str());

  return val::global("window")[dbPromiseName];
}

bool CustomerModel::hasBeenInit() {
  val window = val::global("window");
  return window[isDbLoaded].isTrue();
}

val CustomerModel::persist() {
  EM_ASM({
    let customerCollectionName = UTF8ToString($0);
    let dbName = UTF8ToString($1);
    let dbPromiseName = UTF8ToString($2);

    window[dbPromiseName] = window[dbPromiseName].then(function() {
      return new Promise((resolve, reject) => {
        window[dbName].saveDatabase(function() {
          resolve();
        })
      });
    });
  }, customerCollectionName.c_str(), dbName.c_str(), dbPromiseName.c_str());

  return val::global("window")[dbPromiseName];
}

void CustomerModel::saveCustomer(int studentId) {
  // Returns immediately an attempt to modify the DB is made, when it is not yet
  // loaded. This should throw an exception.
  if (!CustomerModel::hasBeenInit()) {
    return;
  }

  val window = val::global("window");
  val customers = window[dbName].call<val>("getCollection", customerCollectionName);
  val customer = val::object();
  customer.set("studentId", studentId);
  customer.set("name", "Paul McCartney");
  customer.set("age", 75);
  customers.call<val>("insert", customer);
}

void CustomerModel::findCustomers() {
  if (!CustomerModel::hasBeenInit()) {
    return;
  }
  /*
   * Equivalent JS:
   * let customers = window.db.getCollection('customers');
   * let selector = {'name': 'Paul McCartney' };
   * let results = customers.find(selector);
   *
   * See: https://rawgit.com/techfort/LokiJS/master/jsdoc/tutorial-Query%20Examples.html
   */

  val window = val::global("window");
  val customers = window[dbName].call<val>("getCollection", customerCollectionName);
  val selector = val::object();
  selector.set("name", "Paul McCartney");
  val results = customers.call<val>("find", selector);

  unsigned int length = results["length"].as<unsigned int>();
  for(unsigned int i = 0; i < length; ++i) {
    val customer = results[i].as<val>();
    std::cout << customer["name"].as<std::string>() << std::endl;
    std::cout << customer["studentId"].as<int>() << std::endl;
    std::cout << customer["age"].as<int>() << std::endl;
  }
}

bool CustomerModel::isExistingUser(int studentNum){
  if (!CustomerModel::hasBeenInit()) {
    return false;
  }
  // run find query using loki.js
  // if returned vector is not empty, return true (customer exists)
  val window = val::global("window");
  val customers = window[dbName].call<val>("getCollection", customerCollectionName);
  val selector = val::object();
  selector.set("studentId", studentNum);
  val results = customers.call<val>("find", selector);
  unsigned int length = results["length"].as<unsigned int>();
  return (length > 0);
}

// creates a new collection in db, takes name of new collection as argument 
void CustomerModel::createNewCollection(const std::string &collectionName) {
    if (!CustomerModel::hasBeenInit()) {
    return;
  }
  val window = val::global("window");
  val newCol = window[dbName].call<val>("addCollection", collectionName);
}

void CustomerModel::overWriteUser(const json &user) {
  if (!CustomerModel::hasBeenInit()) {
    return;
  }
  std::cout << user << std::endl;
  int id = user["studentId"];
  val window = val::global("window");
  val customers = window[dbName].call<val>("getCollection", customerCollectionName);
  val query = val::object();
  query.set("studentId", id);
  val result = (customers.call<val>("findOne", query));
  result.set("studentId", id);
  result.set("name", user["name"].get<std::string>());
  result.set("age", user["age"].get<int>());
  result.set("order", user["order"].get<std::string>());
}

// just using string object for image instead of Image class for now
// also this assumes that the collection used for the customer images is called "images"
// Maybe we should pass the collection name as an argument in the future...
void CustomerModel::addImageToUser(const std::string &studentId, const std::string &image) {
    // inserting new document into images collection
    // structure of document {studentId: 00000000, image: ""}
    if (!CustomerModel::hasBeenInit()) {
        return;
    }
    val window = val::global("window");
    val imageCol = window[dbName].call<val>("getCollection", imagesCollectionName);
    val document = val::object();
    document.set("studentId", studentId);
    document.set("image", image);
    imageCol.call<val>("insert", document);
}

// In the SDD -> getImagesOfUser(std::string, std::vector<Image*>*, std::string<std::string>*, int)
// currently this function will add images by string to a vector
// I am assuming the int is for when we want a certain number of images
// if this argument is set to -1, return all images for student with studentId
void CustomerModel::getImagesOfUser(const std::string &studentId, std::vector<std::string> &imageVecOut , int) {
    if (!CustomerModel::hasBeenInit()) {
        return;
    }
    val window = val::global("window");
    val images = window[dbName].call<val>("getCollection", imagesCollectionName);
    val selector = val::object();
    selector.set("studentId", studentId);
    val results = images.call<val>("find", selector);
    unsigned int length = results["length"].as<unsigned int>();
    for(unsigned int i = 0; i < length; ++i) {
        val image = results[i].as<val>();
        imageVecOut.push_back(image["image"].as<std::string>());
    }
}
