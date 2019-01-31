#pragma once

class BinaryReader;

enum BinaryType
{
  UnknownBinary,
  ELF64,
  ELF32
};

class TypeDetector
{
public:
  explicit TypeDetector(const BinaryReader& binaryReader);

  BinaryType Type() const;

private:
  BinaryType type_;

  BinaryType CheckForELF(const BinaryReader& binaryReader);
};
