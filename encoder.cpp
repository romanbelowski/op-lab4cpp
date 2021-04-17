#include "encoder.hpp"

using namespace std;

// Збергіає зжатий алгоритмом LZW файл in в файл out
void EncoderLZW::encode(const char *in, const char *out) {
  ifstream input(in, std::ios::in | std::ios::binary);
  ofstream output(out, std::ios::out | std::ios::binary);

  queue<int> codes = get_codes(input);
  save_codes(codes, output);

  input.close();
  output.close();
}

// Повертає дані з потоку input у вигляді черги кодів LZW
queue<int> EncoderLZW::get_codes(istream &input) {
  // Мінімізований файл у вигляді черги кодів з таблиці
  queue<int> output;

  // Ініціалізуємо таблицю кодів початковим алфавітом
  map<string, int> dict;
  for (int i = 0; i < 256; i++)
    dict[string(1, i)] = i;

  char c = 0;
  string w;
  while (input.read(&c, sizeof(c))) {
    w = string(1, c);
    output.push(dict[w]);
  }

  return output;
}

// Зберігає чергу кодів LZW у потік output
void EncoderLZW::save_codes(queue<int> &codes, ostream &output) {
  char low, high;
  while (!codes.empty()) {
    low = codes.front();
    output.write(&low, 1);
    codes.pop();
  }
}
