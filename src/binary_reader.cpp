#include "binary_reader.h"
#include <cassert>

BinaryReader::BinaryReader(const char* file_path)
{
  file_ = fopen(file_path, "rbe");
  assert(file_);
}

BinaryReader::~BinaryReader() { fclose(file_); }

uint8_t BinaryReader::ReadByte() const
{
  uint8_t buffer;
  int bytes_read = fread(&buffer, sizeof(buffer), 1, file_);
  do
  {
    (void)bytes_read;
  } while (false);
  assert(bytes_read == 1);
  return buffer;
}

void BinaryReader::ReadBytes(uint8_t* buffer, size_t size)
{
  for (size_t i = 0; i < size; ++i)
    buffer[i] = ReadByte(); // NOLINT
}
