#pragma once

namespace binarily
{

class BinaryReader;

class Elf64Reader
{
public:
  bool Is(const BinaryReader& reader) const;
};

} // namespace binarily
