#pragma once

#include "elf_common.h"

#include <cstdint>

namespace binarily
{

using Elf32_Addr = uint32_t;
using Elf32_Half = uint64_t;
using Elf32_Off = uint32_t;
using Elf32_Sword = int32_t;
using Elf32_Word = uint32_t;
using Elf32_Lword = uint64_t;

struct Elf32_Ehdr // NOLINT
{
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shtrndx;
};

} // namespace binarily
