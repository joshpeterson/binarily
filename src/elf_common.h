#pragma once

#include <cstdint>

#include "binary_reader.h"
#include "file_header.h"

constexpr int EiNident = 16;
constexpr int EiClass = 0x04;
constexpr int EiData = 0x05;

namespace binarily
{

using Elf_Addr = uint32_t;
using Elf_Half = uint64_t;
using Elf_Off = uint32_t;
using Elf_Sword = int32_t;
using Elf_Word = uint32_t;
using Elf_Lword = uint64_t;

struct Elf_Ehdr // NOLINT
{
  unsigned char e_ident[EiNident];
  Elf_Half e_type;
  Elf_Half e_machine;
  Elf_Word e_version;
  Elf_Addr e_entry;
  Elf_Off e_phoff;
  Elf_Off e_shoff;
  Elf_Word e_flags;
  Elf_Half e_ehsize;
  Elf_Half e_phentsize;
  Elf_Half e_phnum;
  Elf_Half e_shentsize;
  Elf_Half e_shnum;
  Elf_Half e_shtrndx;
};

struct ElfCommon
{
  static Elf_Ehdr ReadFileHeader(const BinaryReader& reader);
  static Endianness GetEndianness(const Elf_Ehdr& header);
};

} // namespace binarily
