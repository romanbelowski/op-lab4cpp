#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class ArchiverLZW {
 private:
  int BITS,      // Максимальна кількість біт для запису коду
      MAX_CODE,  // Максимально можливий код в таблиці (MAX_CODE = 2^BITS - 1)

      pending_out,   // Біти в очікуванні для виводу
      pending_size,  // Кількість біт в очікуванні

      code_size,       // Кількість біт необхідна для запису коду
      code_threshold;  // Межа при якій code_size збільшиться на 1 біт

  void lzw_encode(std::istream &input, std::ostream &output);       // Записує файл з потоку input в потік output використовуючи алгоритм LZW
  void output_code(std::ostream &output, int code, int dict_size);  // Добавляє біти з code в очікування, і по можливості виводить очікування
  void debug_code(std::ostream &output, int code, int dict_size);   // Виводить коди з таблиці в output як текст, для відладки
  void flush_output(std::ostream &output, int flush_size);          // Виводить біти з очікування в потік output, якщо їх більше flush_size

 public:
  ArchiverLZW(const int bits) : BITS(bits), MAX_CODE(pow(2, bits) - 1){};
  void compress(const char *in, const char *out);  // Збергіає зжатий алгоритмом LZW файл in в файл out
};