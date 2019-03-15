set(SOURCES
  "binary_reader_test.cpp"
  "elf_reader_test.cpp"
  "elf32_reader_test.cpp"
  "elf64_reader_test.cpp"
  "logger_test.cpp"
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
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME} catch gsl fmt-header-only)
target_compile_definitions(${TEST_NAME} PRIVATE CATCH_CONFIG_CONSOLE_WIDTH=60)
if (MSVC)
  target_compile_options(${TEST_NAME} PRIVATE "/WX")
  target_compile_options(${TEST_NAME} PRIVATE "/W4")
else()
  target_compile_options(${TEST_NAME} PRIVATE "-Wall")
  target_compile_options(${TEST_NAME} PRIVATE "-Wextra")
  target_compile_options(${TEST_NAME} PRIVATE "-Werror")
  target_compile_options(${TEST_NAME} PRIVATE "-pedantic")
endif()

if (EMSCRIPTEN)
  set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "--embed-file ../../../test/data -s DISABLE_EXCEPTION_CATCHING=2 -s DEMANGLE_SUPPORT=1")
endif(EMSCRIPTEN)
