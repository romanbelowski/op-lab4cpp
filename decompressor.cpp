#include "decompressor.hpp"

#define EOF_CODE 256

using namespace std;

void DecompressorLZW::decompress(const char *in, const char *out) {
  ifstream input(in, ios::in | ios::binary);
  ofstream output(out, ios::out | ios::binary);

  if (!input || !output) {
    cerr << "Cannot open file!" << endl;
    exit(1);
  }

  clog << "Decompressing file " << in;
  lzw_decode(input, output);
  cout << " Done.\nResult written to " << out << endl;

  input.close();
  output.close();
}

void DecompressorLZW::lzw_decode(istream &input, ostream &output) {
  unordered_map<int, string> dict;
  for (int i = 0; i < 256; i++) {
    dict[i] = string(1, i);
  }
  string str;
  int code;
  int next_code = 257;
  int progress_bar_counter;

  while (debug_input_code(input, &code, next_code)) {
    if (!dict.count(code)) {
      dict[code] = str + str[0];
    }
    output << dict[code];
    if (!str.empty() && next_code <= MAX_CODE) {
      dict[next_code++] = str + dict[code][0];
    }
    str = dict[code];

    if (++progress_bar_counter % 1000000 == 0) {
      clog << ".";
    }
  }
}

bool DecompressorLZW::debug_input_code(istream &input, int *code, int dict_size) {
  input >> *code;
  return (*code != EOF_CODE);
}