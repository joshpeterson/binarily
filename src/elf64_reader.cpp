#include "elf64_reader.h"
#include "elf_reader.h"

namespace binarily
{

bool Elf64Reader::Is(const BinaryReader& reader) const
{
  return ElfReader::ElfTypeFor(reader) == ELF64;
}

} // namespace binarily
