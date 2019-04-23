#include <cstring>

#include "binary_reader.h"
#include "elf32_file_header.h"
#include "logger.h"

namespace binarily
{

Elf32FileHeader::Elf32FileHeader(const BinaryReader& reader) : header_()
{
  std::array<uint8_t, sizeof(header_)> buffer{};
  int bytesRead = reader.ReadBytes(buffer);
  LOGF("Read {} bytes from header_ file of {} bytes expected", bytesRead,
       sizeof(header_));
  std::memcpy(&header_, buffer.data(), bytesRead);
}

Bitness Elf32FileHeader::GetBitness() const { return ThirtyTwoBit; }

Endianness Elf32FileHeader::GetEndianness() const
{
  if (header_.e_ident[EI_DATA] == 1)
    return LittleEndian;
  if (header_.e_ident[EI_DATA] == 2)
    return BigEndian;
  return UnknownEndian;
}

} // namespace binarily
