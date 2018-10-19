#include "binary_reader.h"

BinaryReader::BinaryReader(const char* file_path)
{
  file_ = fopen(file_path, "rb");
}

uint8_t BinaryReader::ReadByte() const
{
  uint8_t buffer;
  fread(&buffer, sizeof(buffer), 1, file_);
  return buffer;
}
