#include "binary_reader.h"
#include <cassert>

BinaryReader::BinaryReader(const char* file_path)
{
  file_ = fopen(file_path, "rbe");
  assert(file_ != nullptr);
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

void BinaryReader::ReadBytes(gsl::span<uint8_t> buffer)
{
  for (auto& value : buffer)
    value = ReadByte();
}

void BinaryReader::Reset()
{
  int error = fseek(file_, 0, SEEK_SET);
  do
  {
    (void)error;
  } while (false);
  assert(error == 0);
}
