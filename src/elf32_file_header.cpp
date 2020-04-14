#include <cstring>

#include "binary_reader.h"
#include "elf32_file_header.h"
#include "logger.h"

namespace binarily
{

Elf32FileHeader::Elf32FileHeader(const BinaryReader* reader) : header_()
{
  header_ = ElfCommon::ReadFileHeader(reader);
}

BinaryType Elf32FileHeader::GetType() const { return ELF32; }

Bitness Elf32FileHeader::GetBitness() const { return ThirtyTwoBit; }

Endianness Elf32FileHeader::GetEndianness() const
{
  return ElfCommon::GetEndianness(header_);
}

} // namespace binarily
