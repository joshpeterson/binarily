#pragma once

#include "file_data.h"

namespace binarily
{

class FileHeader
{
public:
  [[nodiscard]] virtual BinaryType GetType() const = 0;
  [[nodiscard]] virtual Bitness GetBitness() const = 0;
  [[nodiscard]] virtual Endianness GetEndianness() const = 0;
};

} // namespace binarily
