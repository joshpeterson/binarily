#pragma once

#include <array>
#include <cstdint>
#include <cstdio>
#include <gsl>

#include "binary_reader.h"

namespace binarily
{

class BinaryFileReader : public BinaryReader
{
public:
  explicit BinaryFileReader(const char* file_path);
  ~BinaryFileReader();

  // Don't allow copy, assignment, or move.
  BinaryFileReader(const BinaryFileReader&) = delete;
  BinaryFileReader& operator=(const BinaryFileReader&) = delete;
  BinaryFileReader(BinaryFileReader&&) = delete;
  BinaryFileReader& operator=(BinaryFileReader&&) = delete;

  bool Exists() const final;

  bool ReadByte(uint8_t& value) const final;
  int ReadBytes(gsl::span<uint8_t> buffer) const final;
  void Reset() final;

private:
  FILE* file_;
  static const int bufferSize_ = 128;
  mutable std::array<uint8_t, bufferSize_> buffer_;
  mutable size_t current_;
  mutable size_t bufferUsedSize_;
};

} // namespace binarily
