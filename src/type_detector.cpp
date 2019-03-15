#include "type_detector.h"
#include "binary_reader.h"
#include "logger.h"
#include <array>
#include <cassert>

namespace binarily
{

TypeDetector::TypeDetector(BinaryReader& binaryReader) : type_(UnknownBinary)
{
  assert(binaryReader.Exists());
  type_ = TypeFor(binaryReader);
}

BinaryType TypeDetector::Type() const { return type_; }

BinaryType TypeDetector::TypeFor(BinaryReader& binaryReader)
{
  if (elf32Reader_.Is(binaryReader))
    return ELF32;

  binaryReader.Reset();

  if (elf64Reader_.Is(binaryReader))
    return ELF64;

  return UnknownBinary;
}

} // namespace binarily
