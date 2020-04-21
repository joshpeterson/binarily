#include "catch.hpp"

#include "file_data.h"
#include "test_utils.h"

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

  SECTION("Can serialize FileDataHeader to JSON")
  {
    FileDataHeader fileDataHeader = {};
    fileDataHeader.type = ELF64;
    fileDataHeader.bitness = SixtyFourBit;
    fileDataHeader.endianness = LittleEndian;

    const char* expected = R"({)"
                           R"("bitness":"64-bit",)"
                           R"("endianness":"Little Endian",)"
                           R"("type":"ELF 64-bit Binary")"
                           R"(})";

    REQUIRE(json(fileDataHeader).dump() == expected);
  }

  SECTION("Can serialize FileData to JSON")
  {
    FileData fileData = {};
    fileData.header.type = ELF64;
    fileData.header.bitness = SixtyFourBit;
    fileData.header.endianness = LittleEndian;

    const char* expected = R"({)"
                           R"("header":)"
                           R"({)"
                           R"("bitness":"64-bit",)"
                           R"("endianness":"Little Endian",)"
                           R"("type":"ELF 64-bit Binary")"
                           R"(})"
                           R"(})";

    REQUIRE(json(fileData).dump() == expected);
  }

  SECTION("Can load FileData for an ELF 32-bit binary")
  {
    auto buffer = TestUtils::LoadFile("../../test/data/simple_elf32");
    auto fileData = FileData::Load(buffer.data(), buffer.size());
    REQUIRE(fileData.header.type == ELF32);
    REQUIRE(fileData.header.bitness == ThirtyTwoBit);
    REQUIRE(fileData.header.endianness == LittleEndian);
  }

  SECTION("Can load FileData for an ELF 64-bit binary")
  {
    auto buffer = TestUtils::LoadFile("../../test/data/simple_elf64");
    auto fileData = FileData::Load(buffer.data(), buffer.size());
    REQUIRE(fileData.header.type == ELF64);
    REQUIRE(fileData.header.bitness == SixtyFourBit);
    REQUIRE(fileData.header.endianness == LittleEndian);
  }

  SECTION("Can load FileData for an unkown binary")
  {
    auto buffer = TestUtils::LoadFile("../../test/data/unknown_binary");
    auto fileData = FileData::Load(buffer.data(), buffer.size());
    REQUIRE(fileData.header.type == UnknownBinary);
    REQUIRE(fileData.header.bitness == UnknownBitness);
    REQUIRE(fileData.header.endianness == UnknownEndian);
  }
}
