#include "binary_file_reader.h"
#include "logger.h"
#include <cassert>

namespace binarily
{

BinaryFileReader::BinaryFileReader(const char* file_path)
    : buffer_(), current_(bufferSize_), bufferUsedSize_(0)
{
  LOGF("Attempting to open file '{}'", file_path);
  file_ = fopen(file_path, "rb");
  LOGF("File open {}: {}", file_ ? "succeeded" : "failed", (void*)file_);
}

BinaryFileReader::~BinaryFileReader()
{
  if (file_ != nullptr)
    fclose(file_);
}

bool BinaryFileReader::Exists() const { return file_ != nullptr; }

bool BinaryFileReader::ReadByte(uint8_t& value) const
{
  if (current_ >= bufferUsedSize_)
  {
    bufferUsedSize_ = fread(buffer_.data(), 1, buffer_.size(), file_);
    if (bufferUsedSize_ == 0)
      return false;
    current_ = 0;
  }
  value = gsl::at(buffer_, current_++);
  return true;
}

int BinaryFileReader::ReadBytes(gsl::span<uint8_t> buffer) const
{
  int bytes = 0;
  for (auto& value : buffer)
  {
    if (!ReadByte(value))
      break;
    bytes++;
  }

  LOGF("Read {} bytes from {}", bytes, (void*)file_);

  return bytes;
}

void BinaryFileReader::Reset()
{
  int error = fseek(file_, 0, SEEK_SET);
  current_ = bufferSize_;
  do
  {
    (void)error;
  } while (false);
  assert(error == 0);
}

} // namespace binarily
