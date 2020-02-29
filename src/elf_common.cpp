#include <cstring>

#include "elf_common.h"
#include "logger.h"

namespace binarily
{

Elf_Ehdr ElfCommon::ReadFileHeader(const BinaryReader* reader)
{
  Elf_Ehdr header = {};
  std::array<uint8_t, sizeof(header)> buffer{};
  int bytesRead = reader->ReadBytes(buffer);
  LOGF("Read {} bytes from header_ file of {} bytes expected", bytesRead,
       sizeof(header));
  std::memcpy(&header, buffer.data(), bytesRead);
  return header;
}

Endianness ElfCommon::GetEndianness(const Elf_Ehdr& header)
{
  if (header.e_ident[EiData] == 1)
    return LittleEndian;
  if (header.e_ident[EiData] == 2)
    return BigEndian;
  return UnknownEndian;
}

} // namespace binarily
