// Compile with
// g++ generate_elf_with_wrong_bitness.cpp -o generate_elf_with_wrong_bitness
#include <cstdint>
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/elf_with_wrong_bitness", "wb");
  // Valid bitness values are 1 (32-bit) or 2 (64-bit), 3 is invalid.
  uint8_t data[] = {0x7F, 0x45, 0x4c, 0x46, 0x03};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
