#include "logger.h"
#include <fmt/format.h>

bool Logger::Enabled = false;

static void StandardOutputLogCallback(const std::string& message)
{
  fmt::print(message);
}

Logger::Logger(LogCallback callback) : callback_(callback)
{
  if (callback_ == nullptr)
    callback_ = StandardOutputLogCallback;
}

void Logger::Write(const std::string& message)
{
  if (Enabled)
    callback_(message);
}
