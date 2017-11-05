/*
 * TestRunner.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: viraj
 */
#include <functional>
#include <iostream>
#include <vector>
#include <string>

#include "test/TestRunner.h"

TestRunner::TestRunner(std::string runnerDescription) : description(runnerDescription) { }

void TestRunner::addTest(const std::function<void()> testFunction,
                         const std::string testDescription) {
  testFunctions.push_back(testFunction);
  testDescriptions.push_back(testDescription);
}

void TestRunner::run() {
  std::cout << "--- Setting up test runner ---\n";
  std::cout << description << std::endl;

  for (unsigned int i = 0; i < testFunctions.size(); i++) {
    std::cout << "Running test #" << i + 1 << std::endl;
    std::cout << "Description: " << testDescriptions[i] << std::endl;
    std::clock_t start = std::clock();

    testFunctions[i]();

    double diff = std::clock() - start;
    std::cout << "Passed! Finished test in: " <<
        static_cast<double>(diff)/CLOCKS_PER_SEC
        << " seconds\n";
  }

  std::cout << "--- Finished running tests ---\n";
}

