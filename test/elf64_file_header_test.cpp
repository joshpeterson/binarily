#include "catch.hpp"

#include "binary_file_reader.h"
#include "elf64_file_header.h"

using namespace binarily;

static Endianness GetEndiannessFor(const char* filePath)
{
  BinaryFileReader reader(filePath);
  Elf64FileHeader header(&reader);
  return header.GetEndianness();
}

TEST_CASE("ELF64 File Header")
{
  SECTION("Knows the proper bitness")
  {
    BinaryFileReader reader("../../test/data/simple_elf64");
    Elf64FileHeader header(&reader);
    REQUIRE(header.GetBitness() == SixtyFourBit);
  }

  SECTION("Can read the proper endianness for little endian")
  {
    REQUIRE(GetEndiannessFor("../../test/data/simple_elf64") == LittleEndian);
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
