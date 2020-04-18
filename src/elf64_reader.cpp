#include "elf64_reader.h"

#include "elf64_file_header.h"
#include "elf_reader.h"

namespace binarily
{

bool Elf64Reader::Is(const BinaryReader* reader)
{
  return ElfReader::ElfTypeFor(reader) == ELF64;
}

FileData Elf64Reader::GetFileData(const BinaryReader* reader)
{
  const Elf64FileHeader header(reader);
  return ElfReader::GetFileData(header);
}

} // namespace binarily
