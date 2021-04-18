#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class ArchiverLZW {
 private:
  // Максимальна кількість біт в коді, що відповідає закодованим символам.
  // Та максимальний розмір таблиці кодів, що залежить від максимальної
  // кількості біт як MAX_CODE = 2^BITS - 1
  int BITS, MAX_CODE;

  int pending_out, pending_size;
  int code_size, current_code, next_bump;

  int count_min_bits(int code);                                // Обчислює мінімальну кількість біт для запису коду
  void lzw_encode(std::istream &input, std::ostream &output);  // Повертає дані з потоку input у вигляді черги кодів LZW
  void output_code(std::ostream &output, int code);
  void debug_code(std::ostream &output, int code);
  void flush_output(std::ostream &output, int flush_size);

 public:
  ArchiverLZW(const int bits) : BITS(bits), MAX_CODE(pow(2, bits) - 1){};
  void compress(const char *in, const char *out);  // Збергіає зжатий алгоритмом LZW файл in в файл out
};