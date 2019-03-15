#pragma once

namespace binarily
{

class BinaryReader;

class Elf32Reader
{
public:
  bool Is(const BinaryReader& reader) const;
};

} // namespace binarily
