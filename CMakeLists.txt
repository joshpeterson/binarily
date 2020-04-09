cmake_minimum_required(VERSION 3.9)

project(binarily CXX)

if (NOT EMSCRIPTEN)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
  add_subdirectory(thirdparty/benchmark)
endif()

if(DEFINED ENV{BINARILY_ENABLE_LOGGING})
  set(ENABLE_LOGGING ON)
else()
  set(ENABLE_LOGGING OFF)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/catch)
add_subdirectory(thirdparty/gsl)
add_subdirectory(thirdparty/fmt)
add_subdirectory(src)
add_subdirectory(test)
if ((NOT EMSCRIPTEN) AND (NOT SANITIZE_ADDRESS) AND (NOT SANITIZE_THREAD) AND (NOT SANITIZE_UNDEFINED))
  add_subdirectory(bench)
endif ()
