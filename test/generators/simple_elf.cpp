// Compile with g++ simple_elf.cpp -o ../data/simple_elf64.cpp
// Compile with g++ -m32 simple_elf.cpp -o ../data/simple_elf32.cpp
#include <cstdio>

int main(int argc, char* argv[])
{
  printf("ELF %s-bit executable\n", sizeof(void*) == 8 ? "64" : "32");
  return 0;
}
