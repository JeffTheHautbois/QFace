#include <iostream>
#include <assert.h>
#include <ctime>
#include "opencv2/core.hpp"

#include "test/test.h"
#include "test/TestRunner.h"
#include "models/MatModel.h"

void stubTest() {
  return;
}

void runTests() {
    TestRunner tr("Runner for reading duck images");
    tr.addTest([]() {
      return;
    }, "Tests if an image can be loaded into a matrix.");

    tr.run();
}
