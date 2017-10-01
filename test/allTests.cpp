#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"

#include "models/stubModel.h"

TEST_CASE("Test the tests", "[test]") {
  REQUIRE(1 == 1);
}
