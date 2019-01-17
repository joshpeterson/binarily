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
  Logger::SetCallback(TestLogCallback);
  actualMessage.clear();

  SECTION("Can log a message")
  {
    const char* expectedMessage = "the clocks were striking thirteen";
    Logger::Write(expectedMessage);
    REQUIRE(actualMessage == expectedMessage);
  }

  SECTION("Can log a formatted message")
  {
    const char* expectedMessage = "the clocks were striking 13";
    const int hour = 13;
    Logger::Write("the clocks were striking {}", hour);
    REQUIRE(actualMessage == expectedMessage);
  }
}
