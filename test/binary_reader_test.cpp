#include "catch.hpp"

#include <array>
#include <cstring>

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

  SECTION("Can read 8 bytes from a file into a std::array")
  {
    std::array<uint8_t, 8> expected = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::array<uint8_t, 8> actual{};
    reader.ReadBytes(actual);
    REQUIRE(actual == expected);
  }

  SECTION("Can read 8 bytes from a file into a std::vector")
  {
    std::vector<uint8_t> expected = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::vector<uint8_t> actual(8);
    reader.ReadBytes(actual);
    REQUIRE(actual == expected);
  }

  SECTION("Can read 8 bytes from a file into a C array")
  {
    uint8_t expected[] = {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00};

    uint8_t actual[8];
    reader.ReadBytes(actual);
    for (int i = 0; i < 8; ++i)
      REQUIRE(std::memcmp((uint8_t*)actual, (uint8_t*)expected, 8) == 0);
  }

  SECTION("Can reset to the start of a file")
  {
    std::array<uint8_t, 8> expected = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::array<uint8_t, 8> unused{};
    reader.ReadBytes(unused);

    reader.Reset();

    std::array<uint8_t, 8> actual{};
    reader.ReadBytes(actual);
    REQUIRE(actual == expected);
  }
}
