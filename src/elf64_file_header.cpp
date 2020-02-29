#include <cstring>

#include "binary_reader.h"
#include "elf64_file_header.h"
#include "elf_common.h"
#include "logger.h"

namespace binarily
{

Elf64FileHeader::Elf64FileHeader(const BinaryReader* reader) : header_()
{
  header_ = ElfCommon::ReadFileHeader(reader);
}

Bitness Elf64FileHeader::GetBitness() const { return SixtyFourBit; }

Endianness Elf64FileHeader::GetEndianness() const
{
  return ElfCommon::GetEndianness(header_);
}

} // namespace binarily
