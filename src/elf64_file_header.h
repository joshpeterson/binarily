#pragma once

#include <array>
#include <cstdint>

#include "elf64.h"
#include "file_header.h"

namespace binarily
{

class BinaryReader;

class Elf64FileHeader : public FileHeader
{
public:
  explicit Elf64FileHeader(const BinaryReader* reader);

  [[nodiscard]] BinaryType GetType() const override;
  [[nodiscard]] Bitness GetBitness() const override;
  [[nodiscard]] Endianness GetEndianness() const override;

private:
  Elf_Ehdr header_;
};

} // namespace binarily
