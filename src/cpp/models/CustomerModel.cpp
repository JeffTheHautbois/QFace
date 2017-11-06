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

#include "models/CustomerModel.h"

using emscripten::val;

const std::string CustomerModel::customerCollectionName = "customers";
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
