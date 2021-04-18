#include <iostream>
#include <string>

#include "compressor.hpp"

using namespace std;

void show_help();

int main(int argc, char *argv[]) {
  if (argc == 4) {
    if (argv[1] == string_view{"--compress"} || argv[1] == string_view{"-c"}) {
      CompressorLZW(12).compress(argv[2], argv[3]);
    } else {
      show_help();
    }
  } else {
    show_help();
  }

  return 0;
}

void show_help() {
  cout << "Simple program to compress and decompress files.\n\n"
          "Syntax: omegazip [options] input_file output_file\n"
          "Options:\n"
          "-h, --help           Print this Help.\n"
          "-c, --compress       Compress file into archive.\n"
          "-d, --decompress     Extract file from archive.\n";
}