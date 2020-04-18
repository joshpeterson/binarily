#pragma once

#include <json.hpp>

using json = nlohmann::json;

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
  UnknownBitness,
  ThirtyTwoBit,
  SixtyFourBit
};

enum Endianness
{
  UnknownEndian,
  BigEndian,
  LittleEndian
};

struct FileDataHeader
{
  BinaryType type;
  Bitness bitness;
  Endianness endianness;
};

struct FileData
{
  FileDataHeader header;

  static FileData Load(const uint8_t* buffer, int size);
};

inline void to_json(json& j, const FileDataHeader& fileDataHeader)
{
  j = json{{"type", fileDataHeader.type},
           {"bitness", fileDataHeader.bitness},
           {"endianness", fileDataHeader.endianness}};
}

inline void to_json(json& j, const FileData& fileData)
{
  j = json{{"header", fileData.header}};
}

inline void to_json(json& j, const BinaryType& type)
{
  switch (type)
  {
  case ELF32:
    j = json("ELF 32-bit Binary");
    break;
  case ELF64:
    j = json("ELF 64-bit Binary");
    break;
  default:
    j = json("Unknown Binary");
  }
}

inline void to_json(json& j, const Bitness& bitness)
{
  switch (bitness)
  {
  case ThirtyTwoBit:
    j = json("32-bit");
    break;
  case SixtyFourBit:
    j = json("64-bit");
    break;
  default:
    j = json("Unknown Bitness");
  }
}

inline void to_json(json& j, const Endianness& endianness)
{
  switch (endianness)
  {
  case LittleEndian:
    j = json("Little Endian");
    break;
  case BigEndian:
    j = json("Big Endian");
    break;
  default:
    j = json("Unknown Endianness");
  }
}

} // namespace binarily
