// Compile with g++ generate_unknown_binary.cpp -o generate_unknown_binary
#include <cstdio>

int main(int argc, char* argv[])
{
  auto file = fopen("../data/unknown_binary", "wb");
  char data[] = {'0', '1', '2', '3', '4', '5', '6', '7'};
  fwrite(data, sizeof(char), sizeof(data), file);
  fclose(file);
  return 0;
}
