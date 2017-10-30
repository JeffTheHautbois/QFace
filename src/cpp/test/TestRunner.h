/*
 * TestRunner.h
 *
 *  Created on: Oct 29, 2017
 *      Author: viraj
 */

#ifndef SRC_CPP_TEST_TESTRUNNER_H_
#define SRC_CPP_TEST_TESTRUNNER_H_


#include <functional>
#include <vector>
#include <string>

class TestRunner {
 public:
  TestRunner(std::string runnerDescription);
  void addTest(const std::function<void()> testFunction,
               const std::string testDescription);
  void run();

 private:
  std::string description;
  std::vector< std::function<void(void)> > testFunctions;
  std::vector< std::string > testDescriptions;
};

#endif /* SRC_CPP_TEST_TESTRUNNER_H_ */
