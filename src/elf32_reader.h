#pragma once

#include "elf32.h"
#include "file_data.h"

namespace binarily
{

class BinaryReader;

class Elf32Reader
{
public:
  static bool Is(const BinaryReader* reader);
  static const FileData GetFileData(const BinaryReader* reader);
};

} // namespace binarily
