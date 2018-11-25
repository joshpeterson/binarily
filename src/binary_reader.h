#pragma once

#include <cstdint>
#include <cstdio>
#include <gsl>

class BinaryReader
{
public:
  BinaryReader(const char* file_path);
  ~BinaryReader();

  bool ReadByte(uint8_t& buffer) const;
  int ReadBytes(gsl::span<uint8_t> buffer);
  void Reset();

private:
  FILE* file_;
};
