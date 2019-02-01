#pragma once

#include <fmt/format.h>
#include <string>

namespace binarily
{

#if defined(ENABLE_LOGGING)
#define LOG(message)                                                           \
  Logger::Write(                                                               \
      fmt::format("{}:{}({}) {}", __FILE__, __LINE__, __func__, message)       \
          .c_str())
#define LOGF(message, ...)                                                     \
  Logger::Write(                                                               \
      fmt::format("{}:{}({}) {}", __FILE__, __LINE__, __func__, message)       \
          .c_str(),                                                            \
      __VA_ARGS__)
#else
#define LOG(message)
#define LOGF(message, ...)
#endif

class Logger
{
public:
  using LogCallback = void (*)(const std::string&);
  static void SetCallback(LogCallback callback);
  static void ResetCallback();

  template <typename... Args>
  static void Write(const char* format, const Args&... args)
  {
    VWrite(format, fmt::make_format_args(args...));
  }

private:
  static LogCallback Callback;

  static void VWrite(const char* format, fmt::format_args args);
};

} // namespace binarily
