#include "binary_reader.h"

BinaryReader::BinaryReader(const char* file_path)
{
  file_ = fopen(file_path, "rb");
}

BinaryReader::~BinaryReader() { fclose(file_); }

uint8_t BinaryReader::ReadByte() const
{
  uint8_t buffer;
  fread(&buffer, sizeof(buffer), 1, file_);
  return buffer;
}

void BinaryReader::ReadBytes(uint8_t* buffer, size_t size)
{
  for (size_t i = 0; i < size; ++i)
    buffer[i] = ReadByte();
}
