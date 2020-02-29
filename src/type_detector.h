#pragma once

#include "binary_type.h"
#include "elf32_reader.h"
#include "elf64_reader.h"

namespace binarily
{

class BinaryReader;

class TypeDetector
{
public:
  explicit TypeDetector(BinaryReader* binaryReader);

  BinaryType Type() const;

private:
  BinaryType type_;

  static BinaryType TypeFor(BinaryReader* binaryReader);
};

} // namespace binarily
