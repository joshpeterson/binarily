#pragma once

#include <array>
#include <cstdint>

#include "elf32.h"
#include "file_header.h"

namespace binarily
{

class BinaryReader;

class Elf32FileHeader : public FileHeader
{
public:
  explicit Elf32FileHeader(const BinaryReader* reader);

  [[nodiscard]] Bitness GetBitness() const override;
  [[nodiscard]] Endianness GetEndianness() const override;

private:
  Elf_Ehdr header_;
};

} // namespace binarily
