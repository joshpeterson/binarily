#include "elf32_reader.h"

#include "elf32_file_header.h"
#include "elf_reader.h"

namespace binarily
{

bool Elf32Reader::Is(const BinaryReader* reader)
{
  return ElfReader::ElfTypeFor(reader) == ELF32;
}

const FileData Elf32Reader::GetFileData(const BinaryReader* reader)
{
  const Elf32FileHeader header(reader);
  return ElfReader::GetFileData(header);
}

} // namespace binarily
