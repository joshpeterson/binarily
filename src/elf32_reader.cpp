#include "elf32_reader.h"
#include "elf_reader.h"

namespace binarily
{

bool Elf32Reader::Is(const BinaryReader& reader) const
{
  return ElfReader::ElfTypeFor(reader) == ELF32;
}

} // namespace binarily
