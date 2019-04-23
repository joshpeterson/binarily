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
  explicit Elf32FileHeader(const BinaryReader& reader);

  Bitness GetBitness() const override;
  Endianness GetEndianness() const override;

private:
  Elf32_Ehdr header_;
};

} // namespace binarily
