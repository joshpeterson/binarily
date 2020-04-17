#include "catch.hpp"

#include "file_data.h"

#include <json.hpp>
#include <string>

#include <cstdio>

using namespace binarily;
using nlohmann::json;

TEST_CASE("File Data")
{
  SECTION("Can serialize BinaryType to JSON")
  {
    REQUIRE(json(UnknownBinary) == "Unknown Binary");
    REQUIRE(json(ELF64) == "ELF 64-bit Binary");
    REQUIRE(json(ELF32) == "ELF 32-bit Binary");
  }

  SECTION("Can serialize Bitness to JSON")
  {
    REQUIRE(json(UnknownBitness) == "Unknown Bitness");
    REQUIRE(json(SixtyFourBit) == "64-bit");
    REQUIRE(json(ThirtyTwoBit) == "32-bit");
  }

  SECTION("Can serialize Endianness to JSON")
  {
    REQUIRE(json(UnknownEndian) == "Unknown Endianness");
    REQUIRE(json(LittleEndian) == "Little Endian");
    REQUIRE(json(BigEndian) == "Big Endian");
  }

  SECTION("Can serialize FileData to JSON")
  {
    FileData fileData;
    fileData.type = ELF64;
    fileData.bitness = SixtyFourBit;
    fileData.endianness = LittleEndian;

    const char* expected = R"({)"
                           R"("bitness":"64-bit",)"
                           R"("endianness":"Little Endian",)"
                           R"("type":"ELF 64-bit Binary")"
                           R"(})";

    REQUIRE(json(fileData).dump() == expected);
  }
}
