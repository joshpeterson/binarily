// Compile with
// g++ generate_elf_without_bitness.cpp -o generate_elf_without_bitness
#include <cstdint>
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/elf_without_bitness", "wb");
  uint8_t data[] = {0x7F, 0x45, 0x4c, 0x46};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
