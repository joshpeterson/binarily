#include "binary_buffer_reader.h"
#include "logger.h"
#include <cassert>

namespace binarily
{

BinaryBufferReader::BinaryBufferReader(const uint8_t* buffer, size_t size)
    : buffer_(buffer), size_(size), current_(0)
{
  LOGF("Read buffer {} of size {}", buffer_, size_);
}

bool BinaryBufferReader::Exists() const { return buffer_ != nullptr; }

bool BinaryBufferReader::ReadByte(uint8_t& value) const
{
  if (current_ + 1 <= size_)
  {
    value = buffer_[current_];
    current_++;
    return true;
  }

  return false;
}

int BinaryBufferReader::ReadBytes(gsl::span<uint8_t> buffer) const
{
  int bytes = 0;
  for (auto& value : buffer)
  {
    if (!ReadByte(value))
      break;
    bytes++;
  }

  LOGF("Read {} bytes from {}", bytes, (void*)buffer_);

  return bytes;
}

const uint8_t* BinaryBufferReader::ReadBytes(int size) const
{
  const uint8_t* value = GetCurrent();
  if (Advance(size))
    return value;
  return nullptr;
}

void BinaryBufferReader::Reset() { current_ = 0; }

bool BinaryBufferReader::Advance(int distance) const
{
  LOGF("Advancing buffer {} (size {}) from {} to {}", buffer_, size_, current_,
       current_ + distance);
  if (current_ + distance > size_)
    return false;

  current_ += distance;
  return true;
}

const uint8_t* BinaryBufferReader::GetCurrent() const
{
  LOGF("Getting buffer {} (size {}) at location {}", buffer_, size_, current_);
  assert(current_ <= size_);
  return &buffer_[current_];
}

} // namespace binarily
