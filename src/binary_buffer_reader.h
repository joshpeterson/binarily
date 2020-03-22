#pragma once

#include <array>
#include <cstdint>
#include <cstdio>
#include <gsl>

#include "binary_reader.h"

namespace binarily
{

class BinaryBufferReader : public BinaryReader
{
public:
  BinaryBufferReader(const uint8_t* buffer, size_t size);

  // BinaryReader interface
  bool Exists() const final;
  bool ReadByte(uint8_t& value) const final;
  int ReadBytes(gsl::span<uint8_t> buffer) const final;
  void Reset() final;

  const uint8_t* ReadBytes(int size) const;

private:
  const uint8_t* buffer_;
  const size_t size_;
  mutable size_t current_;

  bool Advance(int distance) const;
  const uint8_t* GetCurrent() const;
};

} // namespace binarily
