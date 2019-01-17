#include "logger.h"
#include <fmt/format.h>

static void StandardOutputLogCallback(const std::string& message)
{
  fmt::print("{}\n", message);
}

Logger::LogCallback Logger::Callback = StandardOutputLogCallback;

void Logger::SetCallback(LogCallback callback) { Callback = callback; }

void Logger::VWrite(const char* format, fmt::format_args args)
{
  Callback(fmt::vformat(format, args));
}
