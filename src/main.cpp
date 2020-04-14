#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "binary_buffer_reader.h"
#include "type_detector.h"
#include <json.hpp>

using namespace binarily;
using json = nlohmann::json;

int main(int /*argc*/, char** /*argv*/)
{
#if __EMSCRIPTEN__
  EM_ASM("enableFileInput();");
#endif
  return 0;
}

#if __EMSCRIPTEN__
extern "C"
{
  const char* EMSCRIPTEN_KEEPALIVE loadFileData(const uint8_t* buffer, int size)
  {
    json data;
    BinaryBufferReader reader(buffer, size);
    TypeDetector detector(&reader);
    auto type = detector.Type();
    if (type == ELF32)
      data["type"] = "Elf 32-bit";
    else if (type == ELF64)
      data["type"] = "Elf 64-bit";
    else
      data["type"] = "Unknown binary";

    auto jsonString = data.dump();

    // The memory allocated for jsonCopyForJs will be freed on the JavaScript
    // side.
    auto jsonCopyForJs = (char*)malloc(jsonString.size() + 1);
    strcpy(jsonCopyForJs, jsonString.c_str());

    return jsonCopyForJs;
  }
}
#endif
