#include "catch.hpp"

#include <array>
#include <cstdio>
#include <cstring>
#include <vector>

#include <sys/stat.h>

#include "binary_buffer_reader.h"

using namespace binarily;

TEST_CASE("Binary Buffer Reader")
{
  const char* filename = "../../test/data/simple.wasm";
  struct stat stat_buf
  {
  };
  int rc = stat(filename, &stat_buf);
  auto size = rc == 0 ? stat_buf.st_size : -1;
  std::vector<uint8_t> buffer;
  buffer.reserve(size);
  auto file = fopen(filename, "r");
  auto bytes_read = fread(buffer.data(), 1, size, file);
  fclose(file);
  BinaryBufferReader reader(buffer.data(), bytes_read);

  SECTION("Can read first byte from a buffer")
  {
    uint8_t value = 0;
    reader.ReadByte(value);
    REQUIRE(value == 0);
  }

  SECTION("Can read second byte from a buffer")
  {
    uint8_t value = 0;
    reader.ReadByte(value);
    reader.ReadByte(value);
    REQUIRE(value == 0x61);
  }

  SECTION("Can get pointer to current location")
  {
    const uint8_t* value = reader.ReadBytes(2);
    REQUIRE(*value == 0x00);
    REQUIRE(*(value + 1) == 0x61);
  }

  SECTION("ReadBytes advances pointer")
  {
    reader.ReadBytes(2);
    const uint8_t* value = reader.ReadBytes(2);
    REQUIRE(*value == 0x73);
  }

  SECTION("ReadBytes returns nullptr for read too long")
  {
    REQUIRE(reader.ReadBytes(116) == nullptr);
  }

  SECTION("ReadBytes can read entire buffer")
  {
    REQUIRE(reader.ReadBytes(115) != nullptr);
  }

  SECTION("Can copy a BinaryBufferReader")
  {
    // Advance the reader
    reader.ReadBytes(2);

    // Make a copy of the reader at byte 2
    // (don't let clang-tidy try to remove this "unnecessary" copy)
    auto copy = reader; // NOLINT

    // Advance the original reader
    reader.ReadBytes(4);

    // The copy should still be at byte 2
    const uint8_t* value = copy.ReadBytes(2);
    REQUIRE(*value == 0x73);
  }

  SECTION("Can detect end of buffer")
  {
    int bytes = 0;
    uint8_t value = 0;
    while (reader.ReadByte(value))
      bytes++;
    REQUIRE(bytes == 115);
  }

  SECTION("Can read 8 bytes from a buffer into a std::array")
  {
    std::array<uint8_t, 8> expected = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::array<uint8_t, 8> actual{};
    reader.ReadBytes(actual);
    REQUIRE(actual == expected);
  }

  SECTION("Can read 8 bytes from a buffer into a std::vector")
  {
    std::vector<uint8_t> expected = {
        {0x00, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00}};

    std::vector<uint8_t> actual(8);
    reader.ReadBytes(actual);
    REQUIRE(actual == expected);
  }

  SECTION("Can read 8 bytes from a buffer into a C array")
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

  SECTION("Can read entire buffer")
  {
    const int fileSize = 115;
    std::array<uint8_t, fileSize> actual{};
    REQUIRE(reader.ReadBytes(actual) == fileSize);
  }

  SECTION("Don't read beyond end of buffer")
  {
    const int fileSize = 115;
    std::array<uint8_t, 116> actual{};
    REQUIRE(reader.ReadBytes(actual) == fileSize);
  }

  SECTION("Bytes in buffer beyond buffer length are not changed")
  {
    std::array<uint8_t, 116> actual{};
    const uint8_t expectedValue = 0xFE;
    actual[115] = 0xFE;
    reader.ReadBytes(actual);
    REQUIRE(actual[115] == expectedValue);
  }

  SECTION("Can reset to the start of a buffer")
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

  SECTION("Exists returns true for a non-null buffer")
  {
    REQUIRE(reader.Exists());
  }
}

TEST_CASE("Binary buffer reader can handle a missing file")
{
  BinaryBufferReader reader(nullptr, 0);
  REQUIRE(!reader.Exists());
}
