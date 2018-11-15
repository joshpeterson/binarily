#include "binary_reader.h"
#include <benchmark/benchmark.h>
#include <vector>

static void ReadEightBytes(benchmark::State& state)
{
  BinaryReader reader("../../../test/data/simple.wasm");
  for (auto _ : state)
  {
    uint8_t buffer[8];
    reader.ReadBytes(buffer);
    benchmark::DoNotOptimize(buffer);
    reader.Reset();
  }
}

BENCHMARK(ReadEightBytes);
