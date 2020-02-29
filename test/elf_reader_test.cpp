#include "catch.hpp"

#include "binary_file_reader.h"
#include "elf_reader.h"
#include "type_detector.h"

using namespace binarily;

static BinaryType GetTypeFor(const char* filePath)
{
  BinaryFileReader reader(filePath);
  return ElfReader::ElfTypeFor(&reader);
}

TEST_CASE("ELF Reader")
{
  SECTION("An unspecified file is an unknown type")
  {
    REQUIRE(GetTypeFor("../../test/data/unknown_binary") == UnknownBinary);
  }

  SECTION("An one byte file is an unknown type")
  {
    REQUIRE(GetTypeFor("../../test/data/one_byte_file") == UnknownBinary);
  }

  SECTION("Can detect a 64-bit ELF file")
  {
    REQUIRE(GetTypeFor("../../test/data/simple_elf64") == ELF64);
  }

  SECTION("Can detect a 32-bit ELF file")
  {
    REQUIRE(GetTypeFor("../../test/data/simple_elf32") == ELF32);
  }

  SECTION("Can detect a file with an ELF header but no bitness flag")
  {
    REQUIRE(GetTypeFor("../../test/data/elf_without_bitness") == UnknownBinary);
  }

  SECTION("Can detect a file with an ELF header but wrong bitness flag")
  {
    REQUIRE(GetTypeFor("../../test/data/elf_with_wrong_bitness") ==
            UnknownBinary);
  }
}
