#include <iostream>
#include <string>

#include "compressor.hpp"
#include "decompressor.hpp"

void show_help();

int main(int argc, char *argv[]) {
  if (argc == 4) {
    if (argv[1] == std::string_view{"--decompress"} || argv[1] == std::string_view{"-d"}) {
      DecompressorLZW(12).decompress(argv[2], argv[3]);
    } else if (argv[1] == std::string_view{"--compress"} || argv[1] == std::string_view{"-c"}) {
      CompressorLZW(12).compress(argv[2], argv[3]);
    } else {
      show_help();
    }
  } else {
    show_help();
  }
  // DecompressorLZW(12).decompress("text.txt.tar", "text.txt.dec");
  return 0;
}

void show_help() {
  std::cout << "Simple program to compress and decompress files.\n\n"
               "Syntax: omegazip [options] input_file output_file\n"
               "Options:\n"
               "-h, --help           Print this Help.\n"
               "-c, --compress       Compress file into archive.\n"
               "-d, --decompress     Extract file from archive.\n";
}