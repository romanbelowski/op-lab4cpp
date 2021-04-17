#include "encoder.hpp"

using namespace std;

// debug
void printQueue(queue<int> q) {
  while (!q.empty()) {
    cout << " " << q.front();
    q.pop();
  }
  cout << endl;
}

// Збергіає зжатий алгоритмом LZW файл in в файл out
void EncoderLZW::encode(const char *in, const char *out) {
  ifstream input(in, std::ios::in | std::ios::binary);
  ofstream output(out, std::ios::out | std::ios::binary);

  cout << "Compressing file " << in;
  queue<int> codes = get_codes(input);

  printQueue(codes);

  save_codes(codes, output);
  cout << "Result written to " << out << endl;

  input.close();
  output.close();
}

// Повертає дані з потоку input у вигляді черги кодів LZW
queue<int> EncoderLZW::get_codes(istream &input) {
  // Мінімізований файл у вигляді черги кодів з таблиці
  queue<int> output;

  // Ініціалізуємо таблицю кодів початковим алфавітом
  map<string, int> dict;
  for (int i = 0; i < 256; i++) {
    dict[string(1, i)] = i;
  }
  int dict_size = 256;

  char character, progress_bar_counter;
  string w, wc;
  while (input.read(&character, sizeof(character))) {
    wc = w + character;

    if (dict.count(wc)) {  // Послідовність wс є в таблиці
      w = wc;
    } else {  // Послідовності wс немає в таблиці

      output.push(dict[w]);
      w = string(1, character);
      // Добавимо нову послідовність в таблицю
      if (dict_size < MAX_SIZE) {
        dict[wc] = dict_size++;
      }
    }

    // Індикатор прогресу
    if (++progress_bar_counter % 100 == 0) {
      cout << ".";
    }
  }
  cout << " Done." << endl;
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
