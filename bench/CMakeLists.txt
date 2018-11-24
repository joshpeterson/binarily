set(SOURCES
  "binary_reader_bench.cpp"
)

set(LIB_NAME ${PROJECT_NAME}_lib)
set(BENCH_NAME bench)

add_executable(${BENCH_NAME} bench_main.cpp ${SOURCES})
target_link_libraries(${BENCH_NAME} PRIVATE ${LIB_NAME} benchmark gsl)
if (MSVC)
  target_compile_options(${BENCH_NAME} PRIVATE "/W4")
  target_compile_options(${BENCH_NAME} PRIVATE "/WX")
else()
  target_compile_options(${BENCH_NAME} PRIVATE "-Wall")
  target_compile_options(${BENCH_NAME} PRIVATE "-Wextra")
  target_compile_options(${BENCH_NAME} PRIVATE "-Werror")
  target_compile_options(${BENCH_NAME} PRIVATE "-pedantic")
endif()
