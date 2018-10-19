#include "catch.hpp"

#include "binary_reader.h"

TEST_CASE("Can read first byte from a file")
{
  BinaryReader reader("../../test/data/simple.wasm");
  REQUIRE(reader.ReadByte() == 0);
}

TEST_CASE("Can read second byte from a file")
{
  BinaryReader reader("../../test/data/simple.wasm");
  reader.ReadByte();
  REQUIRE(reader.ReadByte() == 0x61);
}
