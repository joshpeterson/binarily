#include "catch.hpp"
#include <string>

#include "logger.h"

std::string actualMessage;

static void TestLogCallback(const std::string& message)
{
  actualMessage = message;
}

TEST_CASE("Logger")
{
  Logger logger(TestLogCallback);
  Logger::Enabled = true;
  actualMessage.clear();

  SECTION("Can log a message")
  {
    const char* expectedMessage = "the clocks were striking thirteen";
    logger.Write(expectedMessage);
    REQUIRE(actualMessage == expectedMessage);
  }

  SECTION("Can be disabled")
  {
    Logger::Enabled = false;
    logger.Write("this message should not be logged");
    REQUIRE(actualMessage.empty());
  }
}
