#include <string>

#include "encoder.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 4 && argv[1] == string_view{"--compress"}) {
    EncoderLZW(12).encode(argv[2], argv[3]);
  }

  return 0;
}