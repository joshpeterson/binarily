#include "catch.hpp"

#include "binary_file_reader.h"
#include "type_detector.h"

using namespace binarily;

TEST_CASE("Type Detector")
{
  SECTION("An unspecified file is an unknown type")
  {
    BinaryFileReader reader("../../test/data/unknown_binary");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == UnknownBinary);
  }

  SECTION("An one byte file is an unknown type")
  {
    BinaryFileReader reader("../../test/data/one_byte_file");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == UnknownBinary);
  }

  SECTION("Can detect a 64-bit ELF file")
  {
    BinaryFileReader reader("../../test/data/simple_elf64");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == ELF64);
  }

  SECTION("Can detect a 32-bit ELF file")
  {
    BinaryFileReader reader("../../test/data/simple_elf32");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == ELF32);
  }

  SECTION("Can detect a file with an ELF header but no bitness flag")
  {
    BinaryFileReader reader("../../test/data/elf_without_bitness");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == UnknownBinary);
  }

  SECTION("Can detect a file with an ELF header but wrong bitness flag")
  {
    BinaryFileReader reader("../../test/data/elf_with_wrong_bitness");
    TypeDetector detector(&reader);
    REQUIRE(detector.Type() == UnknownBinary);
  }
}
