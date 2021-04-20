#include "decompressor.hpp"

#define EOF_CODE 256

using namespace std;

// Збергіає зжатий алгоритмом LZW файл in в файл out
void DecompressorLZW::decompress(const char *in, const char *out) {
  ifstream input(in, ios::in | ios::binary);
  ofstream output(out, ios::out | ios::binary);

  if (!input || !output) {
    cerr << "Cannot open file!" << endl;
    exit(1);
  }

  pending_in = pending_size = 0;
  code_size = 9;
  code_threshold = pow(2, code_size);

  clog << "Decompressing file " << in;
  lzw_decode(input, output);
  cout << " Done.\nResult written to " << out << endl;

  input.close();
  output.close();
}

// Записує файл з потоку input в потік output використовуючи алгоритм LZW
void DecompressorLZW::lzw_decode(istream &input, ostream &output) {
  unordered_map<int, string> dict;
  for (int i = 0; i < 256; i++) {
    dict[i] = string(1, i);
  }
  string str;
  int code;
  int next_code = 257;
  int progress_bar_counter;

  while (input_code(input, &code, next_code)) {
    if (!dict.count(code)) {
      dict[code] = str + str[0];
    }
    output << dict[code];
    if (!str.empty() && next_code <= MAX_CODE) {
      dict[next_code++] = str + dict[code][0];
    }
    str = dict[code];

    // Індикатор прогресу
    if (++progress_bar_counter % 1000000 == 0) {
      clog << ".";
    }
  }
}

// Функція для відладки
bool DecompressorLZW::debug_code(istream &input, int *code, int dict_size) {
  input >> *code;
  return (*code != EOF_CODE);
}

bool DecompressorLZW::input_code(istream &input, int *code, int dict_size) {
  unsigned char in;
  while (pending_size < code_size) {
    input.read((char *)&in, 1);

    pending_in = pending_in | (in << pending_size);
    pending_size += 8;
  }

  int mask = (1 << code_size) - 1;  // Маска на молодші code_size біт
  *code = pending_in & mask;

  pending_in >>= code_size;
  pending_size -= code_size;

  if (dict_size == code_threshold - 1 && dict_size < MAX_CODE) {
    code_threshold *= 2;
    code_size++;
  }
  return (*code != EOF_CODE);
}