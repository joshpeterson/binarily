#include "catch.hpp"

#include "binary_reader.h"
#include "elf32_reader.h"

using namespace binarily;

static bool IsElf32(const char* filePath)
{
  BinaryReader reader(filePath);
  Elf32Reader elf32Reader;
  return elf32Reader.Is(reader);
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
}
