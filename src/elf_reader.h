#pragma once

#include "type_detector.h"

namespace binarily
{

class BinaryReader;

class ElfReader
{
public:
  static BinaryType ElfTypeFor(const BinaryReader* binaryReader);
};

} // namespace binarily
