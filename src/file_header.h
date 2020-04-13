#pragma once

namespace binarily
{

enum Bitness
{
  ThirtyTwoBit,
  SixtyFourBit
};

enum Endianness
{
  UnknownEndian,
  BigEndian,
  LittleEndian
};

class FileHeader
{
public:
  [[nodiscard]] virtual Bitness GetBitness() const = 0;
  [[nodiscard]] virtual Endianness GetEndianness() const = 0;
};

} // namespace binarily
