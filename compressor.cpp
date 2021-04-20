#include "compressor.hpp"

#define EOF_CODE 256

using namespace std;

// Збергіає зжатий алгоритмом LZW файл in в файл out
void CompressorLZW::compress(const char *in, const char *out) {
  ifstream input(in, ios::in | ios::binary);
  ofstream output(out, ios::out | ios::binary);

  if (!input || !output) {
    cerr << "Cannot open file!" << endl;
    exit(1);
  }

  pending_out = pending_size = 0;
  code_size = 9;
  code_threshold = pow(2, code_size);

  clog << "Compressing file " << in;
  lzw_encode(input, output);
  cout << " Done.\nResult written to " << out << endl;

  input.close();
  output.close();
}

// Записує файл з потоку input в потік output використовуючи алгоритм LZW
void CompressorLZW::lzw_encode(istream &input, ostream &output) {
  // Ініціалізуємо таблицю кодів початковим алфавітом
  unordered_map<string, int> dict;
  for (int i = 0; i < 256; i++) {
    dict[string(1, i)] = i;
  }
  int next_code = 257;  // Пропускаємо один для EOF_CODE = 256

  int progress_bar_counter;

  char character;
  string str, next_str;
  while (input.read(&character, 1)) {
    next_str = str + character;

    // Чи присутня послідовність next_str в таблиці
    if (dict.count(next_str)) {
      str = next_str;
    } else {
      // Добавимо нову послідовність next_str в таблицю
      if (next_code <= MAX_CODE) {
        dict[next_str] = next_code++;
      }
      // Виведемо код str
      output_code(output, dict[str], next_code);
      str = string(1, character);
    }

    // Індикатор прогресу
    if (++progress_bar_counter % 1000000 == 0) {
      clog << ".";
    }
  }
  if (!str.empty()) {
    output_code(output, dict[str], next_code);
  }
  output_code(output, EOF_CODE, next_code);
  flush_output(output, 0);
}

// Добавляє біти з code в очікування, і по можливості виводить очікування
void CompressorLZW::output_code(ostream &output, int code, int dict_size) {
  // Добавимо code в очікування
  pending_out = (code << pending_size) | pending_out;
  pending_size += code_size;

  if (dict_size - 1 == code_threshold) {
    code_threshold *= 2;
    code_size++;
  }
  flush_output(output, 8);
}

// Виводить біти з очікування в потік output, якщо їх більше flush_size
void CompressorLZW::flush_output(ostream &output, int flush_size) {
  int out;
  while (pending_size >= flush_size) {
    // Запишемо молодші 8 біт
    out = pending_out & 0xFF;
    output.write((char *)&out, 1);

    // Зсунемось на 8 біт
    pending_out >>= 8;
    pending_size -= 8;
  }
}

// Виводить коди з таблиці в output як текст, для відладки
void CompressorLZW::debug_code(ostream &output, int code, int dict_size) {
  output << code << endl;
}
