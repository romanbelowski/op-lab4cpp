#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>

class EncoderLZW {
 private:
  // Максимальна кількість біт в коді, що відповідає закодованим символам.
  // Та максимальний розмір таблиці кодів, що залежить від максимальної
  // кількості біт як TABLE_SIZE = 2^BITS
  int BITS, TABLE_SIZE;

  int count_min_bits(int n);
  std::queue<int> get_codes(std::istream &input);                 // Повертає дані з потоку input у вигляді черги кодів LZW
  void save_codes(std::queue<int> &codes, std::ostream &output);  // Зберігає чергу кодів LZW у потік output

 public:
  EncoderLZW(const int bits) : BITS(bits), TABLE_SIZE(pow(2, bits)){};
  void encode(const char *in, const char *out);  // Збергіає зжатий алгоритмом LZW файл in в файл out
};