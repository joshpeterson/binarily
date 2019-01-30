#include "type_detector.h"
#include "binary_reader.h"
#include "logger.h"
#include <array>
#include <cassert>

TypeDetector::TypeDetector(const BinaryReader& binaryReader)
    : type_(UnknownBinary)
{
  assert(binaryReader.Exists());
  type_ = CheckForELF(binaryReader);
}

BinaryType TypeDetector::Type() const { return type_; }

BinaryType TypeDetector::CheckForELF(const BinaryReader& binaryReader)
{
  std::array<uint8_t, 4> header{};
  auto bytesRead = binaryReader.ReadBytes(header);
  if (bytesRead == 4)
  {
    LOG("Read 4 bytes of the file header");
    const std::array<uint8_t, 4> elfHeader{{0x7F, 0x45, 0x4c, 0x46}};
    if (header == elfHeader)
    {
      LOG("This looks like an ELF binary");
      const uint8_t bitness_32 = 1;
      const uint8_t bitness_64 = 2;
      uint8_t bitness = 0;
      if (binaryReader.ReadByte(bitness))
      {
        if (bitness == bitness_32)
        {
          LOG("This is a 32-bit ELF binary");
          return ELF32;
        }

        if (bitness == bitness_64)
        {
          LOG("This is a 64-bit ELF binary");
          return ELF64;
        }

        LOGF("Invalid bitness byte value '{}', this is not an ELF binary",
             bitness);
      }
      else
      {
        LOG("Unable to read the fifth byte of the file to determine bitness");
        LOG("This must not be a valid ELF binary");
      }
    }
  }

  return UnknownBinary;
}
