#pragma once

#include <cstdint>
#include <vector>

struct TestUtils
{
  static std::vector<uint8_t> LoadFile(const char* filePath);
};
