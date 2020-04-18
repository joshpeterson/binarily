#include "elf_reader.h"
#include "binary_reader.h"
#include "logger.h"

namespace binarily
{

BinaryType ElfReader::ElfTypeFor(const BinaryReader* binaryReader)
{
  std::array<uint8_t, 4> header{};
  auto bytesRead = binaryReader->ReadBytes(header);
  if (bytesRead == 4)
  {
    LOGF("Read 4 bytes of the file header: {0:#x} {1:#x} {2:#x} {3:#x}",
         header[0], header[1], header[2], header[3]);
    const std::array<uint8_t, 4> elfHeader{{0x7F, 0x45, 0x4c, 0x46}};
    if (header == elfHeader)
    {
      LOG("This looks like an ELF binary");
      const uint8_t bitness_32 = 1;
      const uint8_t bitness_64 = 2;
      uint8_t bitness = 0;
      if (binaryReader->ReadByte(bitness))
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

FileData ElfReader::GetFileData(const FileHeader& header)
{
  FileData fileData = {};
  fileData.header.type = header.GetType();
  fileData.header.bitness = header.GetBitness();
  fileData.header.endianness = header.GetEndianness();

  return fileData;
}

} // namespace binarily
