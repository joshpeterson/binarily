// Compile with g++ generate_one_byte_file.cpp -o generate_one_byte_file
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/one_byte_file", "wb");
  char data[] = {'2'};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
