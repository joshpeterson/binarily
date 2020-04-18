#include "file_data.h"

#include <json.hpp>

#include "binary_buffer_reader.h"
#include "elf32_reader.h"
#include "elf64_reader.h"
#include "type_detector.h"

using nlohmann::json;

namespace binarily
{

FileData FileData::Load(const uint8_t* buffer, int size)
{
  BinaryBufferReader reader(buffer, size);
  TypeDetector detector(&reader);
  auto type = detector.Type();
  if (type == ELF32)
    return Elf32Reader::GetFileData(&reader);
  if (type == ELF64)
    return Elf64Reader::GetFileData(&reader);

  FileData fileData = {};
  return fileData;
}

} // namespace binarily
