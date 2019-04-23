#include "catch.hpp"

#include "binary_reader.h"
#include "elf32_file_header.h"

using namespace binarily;

static Endianness GetEndiannessFor(const char* filePath)
{
  BinaryReader reader(filePath);
  Elf32FileHeader header(reader);
  return header.GetEndianness();
}

TEST_CASE("ELF32 File Header")
{
  SECTION("Knows the proper bitness")
  {
    BinaryReader reader("../../test/data/simple_elf32");
    Elf32FileHeader header(reader);
    REQUIRE(header.GetBitness() == ThirtyTwoBit);
  }

  SECTION("Can read the proper endianness for little endian")
  {
    REQUIRE(GetEndiannessFor("../../test/data/simple_elf32") == LittleEndian);
  }

  SECTION("Can read the proper endianness for big endian")
  {
    REQUIRE(GetEndiannessFor("../../test/data/elf_with_big_endianness") ==
            BigEndian);
  }

  SECTION("Can read the proper endianness for unknown endian")
  {
    REQUIRE(GetEndiannessFor("../../test/data/elf_with_wrong_endianness") ==
            UnknownEndian);
  }
}
