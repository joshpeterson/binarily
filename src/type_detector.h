#pragma once

#include "elf32_reader.h"
#include "elf64_reader.h"
#include "file_data.h"

namespace binarily
{

class BinaryReader;

class TypeDetector
{
public:
  explicit TypeDetector(BinaryReader* binaryReader);

  [[nodiscard]] BinaryType Type() const;

private:
  BinaryType type_;

  static BinaryType TypeFor(BinaryReader* binaryReader);
};

} // namespace binarily
