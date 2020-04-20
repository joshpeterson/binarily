set(SOURCES
  "binary_reader.h"
  "binary_buffer_reader.h"
  "binary_buffer_reader.cpp"
  "binary_file_reader.h"
  "binary_file_reader.cpp"
  "elf_common.h"
  "elf_common.cpp"
  "elf_reader.h"
  "elf_reader.cpp"
  "elf32.h"
  "elf32_file_header.h"
  "elf32_file_header.cpp"
  "elf32_reader.h"
  "elf32_reader.cpp"
  "elf64.h"
  "elf64_file_header.h"
  "elf64_file_header.cpp"
  "elf64_reader.h"
  "elf64_reader.cpp"
  "file_data.h"
  "file_data.cpp"
  "file_header.h"
  "logger.h"
  "logger.cpp"
  "type_detector.h"
  "type_detector.cpp"
)

find_package(Sanitizers)

set(LIB_NAME ${PROJECT_NAME}_lib)

add_library(${LIB_NAME} STATIC ${SOURCES})
add_sanitizers(${LIB_NAME})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${LIB_NAME} PRIVATE gsl)
target_link_libraries(${LIB_NAME} PRIVATE fmt-header-only)
target_link_libraries(${LIB_NAME} PRIVATE json)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

SET_SOURCE_FILES_PROPERTIES(main.cpp PROPERTIES OBJECT_DEPENDS ${CMAKE_SOURCE_DIR}/web/shell_minimal.html)

add_executable(${PROJECT_NAME} main.cpp)
add_sanitizers(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME} gsl)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME} json)
if (MSVC)
  target_compile_options(${LIB_NAME} PRIVATE "/W4")
  target_compile_options(${LIB_NAME} PRIVATE "/WX")
  target_compile_options(${LIB_NAME} PRIVATE "/EHsc-")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(${LIB_NAME} PRIVATE "-Wall")
  target_compile_options(${LIB_NAME} PRIVATE "-Wextra")
  target_compile_options(${LIB_NAME} PRIVATE "-Werror")
  target_compile_options(${LIB_NAME} PRIVATE "-pedantic")
  target_compile_options(${LIB_NAME} PRIVATE "-fno-exceptions")
  target_compile_options(${LIB_NAME} PRIVATE "-fno-rtti")
endif()

if (EMSCRIPTEN)
  configure_file(${CMAKE_SOURCE_DIR}/web/binarily.svg binarily.svg COPYONLY)
  configure_file(${CMAKE_SOURCE_DIR}/web/favicon.ico favicon.ico COPYONLY)
  set(CMAKE_EXE_LINKER_FLAGS "--shell-file ${CMAKE_SOURCE_DIR}/web/shell_minimal.html -s NO_EXIT_RUNTIME=1  -s \"EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']\"")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


option(ENABLE_LOGGING "Enable logging" OFF)
if(ENABLE_LOGGING)
  add_definitions(-DENABLE_LOGGING)
endif(ENABLE_LOGGING)

