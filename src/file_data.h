#pragma once

namespace binarily
{

enum BinaryType
{
  UnknownBinary,
  ELF64,
  ELF32
};

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

struct FileData
{
  BinaryType type;
  Bitness bitness;
  Endianness endianness;
};

} // namespace binarily
