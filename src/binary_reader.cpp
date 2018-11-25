#include "binary_reader.h"
#include <cassert>

BinaryReader::BinaryReader(const char* file_path)
{
  file_ = fopen(file_path, "rb");
  assert(file_ != nullptr);
}

BinaryReader::~BinaryReader() { fclose(file_); }

bool BinaryReader::ReadByte(uint8_t& buffer) const
{
  size_t bytes_read = fread(&buffer, sizeof(buffer), 1, file_);
  return bytes_read == 1;
}

int BinaryReader::ReadBytes(gsl::span<uint8_t> buffer)
{
  int bytes = 0;
  for (auto& value : buffer)
  {
    if (!ReadByte(value))
      break;
    bytes++;
  }

  return bytes;
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
