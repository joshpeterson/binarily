set(SOURCES
  "binary_reader_bench.cpp"
)

set(LIB_NAME ${PROJECT_NAME}_lib)
set(BENCH_NAME bench)

add_executable(${BENCH_NAME} bench_main.cpp ${SOURCES})
target_link_libraries(${BENCH_NAME} PRIVATE ${LIB_NAME} benchmark gsl)
