#include "catch.hpp"

#include "binary_file_reader.h"
#include "elf32_reader.h"

using namespace binarily;

static bool IsElf32(const char* filePath)
{
  BinaryFileReader reader(filePath);
  return Elf32Reader::Is(&reader);
}

static FileData GetFileData(const char* filePath)
{
  BinaryFileReader reader(filePath);
  return Elf32Reader::GetFileData(&reader);
}

TEST_CASE("ELF 32-bit Reader")
{
  SECTION("An unspecified file is not ELF 32-bit")
  {
    REQUIRE(!IsElf32("../../test/data/unknown_binary"));
  }

  SECTION("A 64-bit ELF file is not ELF 32-bit")
  {
    REQUIRE(!IsElf32("../../test/data/simple_elf64"));
  }

  SECTION("A 32-bit ELF file is correctly identified")
  {
    REQUIRE(IsElf32("../../test/data/simple_elf32"));
  }

  SECTION("Returns file data with proper type")
  {
    auto fileData = GetFileData("../../test/data/simple_elf32");
    REQUIRE(fileData.type == ELF32);
  }

  SECTION("Returns file data with proper bitness")
  {
    auto fileData = GetFileData("../../test/data/simple_elf32");
    REQUIRE(fileData.bitness == ThirtyTwoBit);
  }

  SECTION("Returns file data with proper endianness")
  {
    auto fileData = GetFileData("../../test/data/simple_elf32");
    REQUIRE(fileData.endianness == LittleEndian);
  }
}
