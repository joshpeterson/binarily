#pragma once

#include <cstdint>
#include <cstdio>

class BinaryReader
{
public:
  BinaryReader(const char* file_path);
  uint8_t ReadByte() const;

private:
  FILE* file_;
};
