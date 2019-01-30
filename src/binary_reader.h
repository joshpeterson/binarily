#pragma once

#include <array>
#include <cstdint>
#include <cstdio>
#include <gsl>

class BinaryReader
{
public:
  explicit BinaryReader(const char* file_path);
  ~BinaryReader();

  // Don't allow copy, assignment, or move.
  BinaryReader(const BinaryReader&) = delete;            // copy constructor
  BinaryReader& operator=(const BinaryReader&) = delete; // copy assignment
  BinaryReader(BinaryReader&&) = delete;                 // move constructor
  BinaryReader& operator=(BinaryReader&&) = delete;      // move assignment

  bool Exists() const;

  bool ReadByte(uint8_t& value) const;
  int ReadBytes(gsl::span<uint8_t> buffer) const;
  void Reset();

private:
  FILE* file_;
  static const int bufferSize_ = 128;
  mutable std::array<uint8_t, bufferSize_> buffer_;
  mutable size_t current_;
  mutable size_t bufferUsedSize_;
};
