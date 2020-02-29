#include "catch.hpp"

#include "binary_file_reader.h"
#include "elf64_reader.h"

using namespace binarily;

static bool IsElf64(const char* filePath)
{
  BinaryFileReader reader(filePath);
  return Elf64Reader::Is(&reader);
}

TEST_CASE("ELF 64-bit Reader")
{
  SECTION("An unspecified file is not ELF 64-bit")
  {
    REQUIRE(!IsElf64("../../test/data/unknown_binary"));
  }

  SECTION("A 32-bit ELF file is not ELF 64-bit")
  {
    REQUIRE(!IsElf64("../../test/data/simple_elf32"));
  }

  SECTION("A 64-bit ELF file is correctly identified")
  {
    REQUIRE(IsElf64("../../test/data/simple_elf64"));
  }
}
