// Compile with
// g++ generate_elf_with_wrong_endianness.cpp -o
// generate_elf_with_wrong_endianness
#include <cstdint>
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/elf_with_wrong_endianness", "wb");
  // Valid endianness values are 1 (little) or 2 (big), 3 is invalid.
  uint8_t data[] = {0x7F, 0x45, 0x4c, 0x46, 0x01, 0x03};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
