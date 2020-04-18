#pragma once

#include "file_data.h"
#include "type_detector.h"

namespace binarily
{

class BinaryReader;
class FileHeader;

class ElfReader
{
public:
  static BinaryType ElfTypeFor(const BinaryReader* binaryReader);
  static FileData GetFileData(const FileHeader& header);
};

} // namespace binarily
