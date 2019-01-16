#pragma once

#include <string>

#if defined(ENABLE_LOGGING)
#define LOG_WRITE(message) Logger::Write(message)
#else
#define LOG_WRITE(message)
#endif

class Logger
{
public:
  using LogCallback = void (*)(const std::string&);
  static void SetCallback(LogCallback callback);

  static void Write(const std::string& message);

private:
  static LogCallback Callback;
};
