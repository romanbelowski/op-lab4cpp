#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class DecompressorLZW {
 private:
  int BITS,      // Максимальна кількість біт для запису коду
      MAX_CODE,  // Максимально можливий код в таблиці (MAX_CODE = 2^BITS - 1)

      pending_in,    // Біти в очікуванні для вводу
      pending_size,  // Кількість біт в очікуванні

      code_size,       // Кількість біт необхідна для запису коду
      code_threshold;  // Межа при якій code_size збільшиться на 1 біт

  void lzw_decode(std::istream &input, std::ostream &output);      // Записує файл з потоку input в потік output використовуючи алгоритм LZW
  bool input_code(std::istream &input, int *code, int dict_size);  // Добавляє біти з code в очікування
  bool debug_code(std::istream &input, int *code, int dict_size);  // Виводить коди з таблиці в output як текст, для відладки

 public:
  DecompressorLZW(const int bits) : BITS(bits), MAX_CODE(pow(2, bits) - 1){};
  void decompress(const char *in, const char *out);  // Збергіає розжатий алгоритмом LZW файл in в файл out
};