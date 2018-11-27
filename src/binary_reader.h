#pragma once

#include <array>
#include <cstdint>
#include <cstdio>
#include <gsl>

class BinaryReader
{
public:
  BinaryReader(const char* file_path);
  ~BinaryReader();

  bool ReadByte(uint8_t& value) const;
  int ReadBytes(gsl::span<uint8_t> buffer);
  void Reset();

private:
  FILE* file_;
  static const int bufferSize_ = 128;
  mutable std::array<uint8_t, bufferSize_> buffer_;
  mutable size_t current_;
  mutable size_t bufferUsedSize_;
};
