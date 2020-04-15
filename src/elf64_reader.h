#pragma once

#include "file_data.h"

namespace binarily
{

class BinaryReader;

class Elf64Reader
{
public:
  static bool Is(const BinaryReader* reader);
  static const FileData GetFileData(const BinaryReader* reader);
};

} // namespace binarily
