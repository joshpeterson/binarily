#pragma once

#include "elf32.h"

namespace binarily
{

class BinaryReader;

class Elf32Reader
{
public:
  static bool Is(const BinaryReader* reader);
};

} // namespace binarily
