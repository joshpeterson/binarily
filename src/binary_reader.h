#pragma once

#include <cstdint>
#include <cstdio>
#include <gsl>

class BinaryReader
{
public:
  BinaryReader(const char* file_path);
  ~BinaryReader();

  uint8_t ReadByte() const;
  void ReadBytes(gsl::span<uint8_t> buffer);
  void Reset();

private:
  FILE* file_;
};
