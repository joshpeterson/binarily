set(SOURCES
  "binary_buffer_reader_test.cpp"
  "binary_file_reader_test.cpp"
  "elf_reader_test.cpp"
  "elf32_file_header_test.cpp"
  "elf32_reader_test.cpp"
  "elf64_file_header_test.cpp"
  "elf64_reader_test.cpp"
  "file_data_test.cpp"
  "logger_test.cpp"
  "test_utils.h"
  "test_utils.cpp"
  "type_detector_test.cpp"
)

find_package(Sanitizers)

set(LIB_NAME ${PROJECT_NAME}_lib)

if (EMSCRIPTEN)
  set(TEST_NAME tests.js)
else(EMSCRIPTEN)
  set(TEST_NAME tests)
endif(EMSCRIPTEN)

add_executable(${TEST_NAME} test_main.cpp ${SOURCES})
add_sanitizers(${TEST_NAME})
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME} catch gsl fmt-header-only json)
target_compile_definitions(${TEST_NAME} PRIVATE CATCH_CONFIG_CONSOLE_WIDTH=60)
if (MSVC)
  target_compile_options(${TEST_NAME} PRIVATE "/WX")
  target_compile_options(${TEST_NAME} PRIVATE "/W4")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(${TEST_NAME} PRIVATE "-Wall")
  target_compile_options(${TEST_NAME} PRIVATE "-Wextra")
  target_compile_options(${TEST_NAME} PRIVATE "-Werror")
  target_compile_options(${TEST_NAME} PRIVATE "-pedantic")
  target_compile_options(${TEST_NAME} PRIVATE "-fno-rtti")
endif()

if (EMSCRIPTEN)
  set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "--embed-file ../../../test/data -s DISABLE_EXCEPTION_CATCHING=2 -s DEMANGLE_SUPPORT=1")
endif(EMSCRIPTEN)
