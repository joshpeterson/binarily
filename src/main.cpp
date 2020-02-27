#include <cstdio>
#include <emscripten/emscripten.h>

#include "binary_buffer_reader.h"
#include "type_detector.h"

using namespace binarily;

int main(int /*argc*/, char** /*argv*/)
{
  EM_ASM("enableFileInput();");
  return 0;
}

extern "C"
{
  const char* EMSCRIPTEN_KEEPALIVE loadFileData(const uint8_t* buffer, int size)
  {
    BinaryBufferReader reader(buffer, size);
    TypeDetector detector(&reader);
    auto type = detector.Type();
    if (type == ELF32)
      return "Elf 32-bit";
    if (type == ELF64)
      return "Elf 64-bit";

    return "Unknown binary";
  }
}
