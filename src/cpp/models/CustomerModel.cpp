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

#include "models/CustomerModel.h"

namespace CustomerModel {
  using emscripten::val;

  const val window = val::global("window");
  const std::string customerCollectionName = "customers";
  const std::string dbPromiseName = "dbPromise";

  void initDb() {
    /*
     * Init the DB. This must be called in main(). If it not called,
     * you will get a bunch of undefined errors.
     */
    val dbPromise = val::global("Promise").call<val>("resolve");
    val::global("window").set(dbPromiseName, dbPromise);

    EM_ASM({
      let customerCollectionName = UTF8ToString($0);

      let initdb = function() {
        var promise = new Promise((resolve, reject) => {
          let databaseInitialize = function () {
            if (!window.db.getCollection(customerCollectionName)) {
                window.db.addCollection(customerCollectionName);
            }
            console.log('Db has been init');
            return resolve('Db has been init');
          };

          var idbAdapter = new LokiIndexedAdapter();
          var lokiArgs = {};
          lokiArgs.adapter = idbAdapter;
          lokiArgs.autoload = true;
          lokiArgs.autosave = true;
          lokiArgs.autoSaveInterval = 5000;
          lokiArgs.autoloadCallback = databaseInitialize;
          window.db = new loki('Turbo.db', lokiArgs);
        });

        return promise;

      };

      window['dbPromise'] = window['dbPromise'].then(initdb);
    }, customerCollectionName.c_str());

  }

  void saveCustomer(std::string id) {
    /*
     Equivalent JS:
     let customers = db.getCollection(customerCollectionName);

     customer = {};
     customer.id = id;
     customer.name = "Paul McCartney";
     customer.age = 75;

     customers.insert(customer);

     NOTE: This insertion is not persisted until initDB auto saves OR is synced.
    */

    EM_ASM({
      window['dbPromise'].then(function() {
       let customers = db.getCollection('customers');

       customer = {};
       customer.id = '10186023';
       customer.name = 'Paul McCartney';
       customer.age = 75;

       console.log('inserting customer');
       customers.insert(customer);
      });
    });

//    val customers = window["db"].call<val>("getCollection", customerCollectionName);
//
//    val customer = val::object();
//    customer.set("id", id);
//    customer.set("name", "Paul McCartney");
//    customer.set("age", 75);
//
//    customers.call<val>("insert", customer);
//    std::cout << "Inserted" << std::endl;

    return;
  }
}
