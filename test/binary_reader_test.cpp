#include "catch.hpp"

#include <array>
#include <cstring>

#include "binary_reader.h"

using namespace binarily;

TEST_CASE("Binary Reader")
{
  BinaryReader reader("../../test/data/simple.wasm");

  SECTION("Can read first byte from a file")
  {
    uint8_t value = 0;
    reader.ReadByte(value);
    REQUIRE(value == 0);
  }

  SECTION("Can read second byte from a file")
  {
    uint8_t value = 0;
    reader.ReadByte(value);
    reader.ReadByte(value);
    REQUIRE(value == 0x61);
  }

  SECTION("Can detect end of file")
  {
    int bytes = 0;
    uint8_t value = 0;
    while (reader.ReadByte(value))
      bytes++;
    REQUIRE(bytes == 115);
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

  SECTION("ReadBytes returns the number of bytes actually read")
  {
    const int expectedSize = 8;
    std::array<uint8_t, expectedSize> actual{};
    REQUIRE(reader.ReadBytes(actual) == expectedSize);
  }

  SECTION("Can read entire file")
  {
    const int fileSize = 115;
    std::array<uint8_t, fileSize> actual{};
    REQUIRE(reader.ReadBytes(actual) == fileSize);
  }

  SECTION("Don't read beyond end of file")
  {
    const int fileSize = 115;
    std::array<uint8_t, 116> actual{};
    REQUIRE(reader.ReadBytes(actual) == fileSize);
  }

  SECTION("Bytes in buffer beyond file are not changed")
  {
    std::array<uint8_t, 116> actual{};
    const uint8_t expectedValue = 0xFE;
    actual[115] = 0xFE;
    reader.ReadBytes(actual);
    REQUIRE(actual[115] == expectedValue);
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

  SECTION("Exists returns true for a file that exists")
  {
    REQUIRE(reader.Exists());
  }
}

TEST_CASE("Can handle a missing file")
{
  BinaryReader reader("Does not exist");
  REQUIRE(!reader.Exists());
}
