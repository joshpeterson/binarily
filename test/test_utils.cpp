#include "test_utils.h"

#include <cassert>
#include <cstdio>
#include <sys/stat.h>

std::vector<uint8_t> TestUtils::LoadFile(const char* filePath)
{
  struct stat stat_buf
  {
  };
  int rc = stat(filePath, &stat_buf);
  auto size = rc == 0 ? stat_buf.st_size : -1;
  std::vector<uint8_t> buffer(size);
  auto file = fopen(filePath, "r");
  auto bytes_read = fread(buffer.data(), 1, size, file);
  (void)bytes_read;
  assert(bytes_read == buffer.size());
  fclose(file);

  return buffer;
}
