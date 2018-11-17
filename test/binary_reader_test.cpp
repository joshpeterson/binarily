#include "catch.hpp"

#include <array>

#include "binary_reader.h"

TEST_CASE("Binary Reader")
{
  BinaryReader reader("../../test/data/simple.wasm");

  SECTION("Can read first byte from a file")
  {
    REQUIRE(reader.ReadByte() == 0);
  }

  SECTION("Can read second byte from a file")
  {
    reader.ReadByte();
    REQUIRE(reader.ReadByte() == 0x61);
  }

  SECTION("Can read 8 bytes from a file")
  {
    std::array<uint8_t, 8> expected_buffer = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::array<uint8_t, 8> actual_buffer{};
    reader.ReadBytes(actual_buffer.data(), actual_buffer.size());
    REQUIRE(actual_buffer == expected_buffer);
  }
}
