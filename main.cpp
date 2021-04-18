#include <string>

#include "archiver.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 4 && argv[1] == string_view{"--compress"}) {
    ArchiverLZW(12).compress(argv[2], argv[3]);
  }

  return 0;
}