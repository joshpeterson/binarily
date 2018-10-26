#pragma once

#include <cstdint>
#include <cstdio>

class BinaryReader
{
public:
  BinaryReader(const char* file_path);
  ~BinaryReader();

  uint8_t ReadByte() const;
  void ReadBytes(uint8_t* buffer, size_t size);

private:
  FILE* file_;
};
