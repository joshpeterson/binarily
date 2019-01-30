#include "catch.hpp"
#include <string>

#include "logger.h"

std::string actualMessage;

static void TestLogCallback(const std::string& message)
{
  actualMessage = message;
}

class LoggerTestFixture
{
public:
  LoggerTestFixture() { Logger::SetCallback(TestLogCallback); }

  ~LoggerTestFixture()
  {
    actualMessage.clear();
    Logger::ResetCallback();
  }

  LoggerTestFixture(const LoggerTestFixture&) = delete;
  LoggerTestFixture& operator=(const LoggerTestFixture&) = delete;
  LoggerTestFixture(LoggerTestFixture&&) = delete;
  LoggerTestFixture& operator=(LoggerTestFixture&&) = delete;
};

TEST_CASE_METHOD(LoggerTestFixture, "Can log a message")
{
  const char* expectedMessage = "the clocks were striking thirteen";
  Logger::Write(expectedMessage);
  REQUIRE(actualMessage == expectedMessage);
}

TEST_CASE_METHOD(LoggerTestFixture, "Can log a formatted message")
{
  const char* expectedMessage = "the clocks were striking 13";
  const int hour = 13;
  Logger::Write("the clocks were striking {}", hour);
  REQUIRE(actualMessage == expectedMessage);
}
