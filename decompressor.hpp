#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class DecompressorLZW {
 private:
  int BITS,      // Максимальна кількість біт для запису коду
      MAX_CODE;  // Максимально можливий код в таблиці (MAX_CODE = 2^BITS - 1)

  void lzw_decode(std::istream &input, std::ostream &output);            // Записує файл з потоку input в потік output використовуючи алгоритм LZW
  bool debug_input_code(std::istream &input, int *code, int dict_size);  // Виводить коди з таблиці в output як текст, для відладки

 public:
  DecompressorLZW(const int bits) : BITS(bits), MAX_CODE(pow(2, bits) - 1){};
  void decompress(const char *in, const char *out);  // Збергіає розжатий алгоритмом LZW файл in в файл out
};