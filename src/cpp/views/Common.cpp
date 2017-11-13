/*
 * Common.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: viraj
 */

#include "models/TemporaryStorage.h"
#include "models/Database.h"
#include <emscripten/val.h>

#include "emscripten/bind.h"


void clearTemporaryStorage() {
  TemporaryStorage::clearStorage();
}

emscripten::val persist() {
  return Database::persist();
}

EMSCRIPTEN_BINDINGS(Common) {
  emscripten::function("persist", &persist);
  emscripten::function("clearTemporaryStorage", &clearTemporaryStorage);
}
