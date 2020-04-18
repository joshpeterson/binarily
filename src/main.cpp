#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <json.hpp>

#include "file_data.h"

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
    json fileData(FileData::Load(buffer, size));

    // The memory allocated for jsonCopyForJs will be freed on the JavaScript
    // side.
    auto jsonString = fileData.dump();
    auto jsonCopyForJs = (char*)malloc(jsonString.size() + 1);
    strcpy(jsonCopyForJs, jsonString.c_str());

    return jsonCopyForJs;
  }
}
#endif
