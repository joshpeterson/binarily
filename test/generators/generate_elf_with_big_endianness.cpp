// Compile with
// g++ generate_elf_with_big_endianness.cpp -o generate_elf_with_big_endianness
#include <cstdint>
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/elf_with_big_endianness", "wb");
  // Valid endianness values are 1 (little) or 2 (big).
  uint8_t data[] = {0x7F, 0x45, 0x4c, 0x46, 0x01, 0x02};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
