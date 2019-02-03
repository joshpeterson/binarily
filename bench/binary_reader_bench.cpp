#include "binary_reader.h"
#include <array>
#include <benchmark/benchmark.h>

using namespace binarily;

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

static void ReadWholeFile(benchmark::State& state)
{
  for (auto _ : state)
  {
    BinaryReader reader("../../../test/data/simple.wasm");
    std::array<uint8_t, 115> buffer{};
    reader.ReadBytes(buffer);
    benchmark::DoNotOptimize(buffer);
  }
}

BENCHMARK(ReadWholeFile);
