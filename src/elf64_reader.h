#pragma once

namespace binarily
{

class BinaryReader;

class Elf64Reader
{
public:
  static bool Is(const BinaryReader* reader);
};

} // namespace binarily
