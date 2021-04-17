#include "encoder.hpp"

// debug
#include <bitset>

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

  if (!input || !output) {
    cout << "Cannot open file!" << endl;
    exit(1);
  }

  cout << "Compressing file " << in;
  queue<int> codes = get_codes(input);

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
  int output_bit_count = 0, curr, curr_bits, prev = 0, prev_bits = 0, out, offset, mask;
  while (!codes.empty()) {
    curr = codes.front();
    curr_bits = count_min_bits(curr);

    offset = 8 - output_bit_count % 8;

    if (offset == 8 && prev_bits != 0) {
      output.write((char *)&prev, 1);
      prev = prev_bits = 0;
    }

    out = (curr >> (curr_bits - offset));  // Старші (offset) бітів
    out |= prev;                           // Об'єднаємо з попередніми бітами
    output.write((char *)&out, 1);

    cout << curr << ",\t" << out << ",\t" << bitset<8>(out) << ", ";

    prev = 0 | (curr & ((1 << (curr_bits - offset)) - 1));  // Молодші (curr_bits - offset) бітів
    prev = prev << (8 - curr_bits + offset);

    prev_bits = 8 - offset;
    output_bit_count += curr_bits;

    cout << prev_bits << ",\t" << bitset<8>(prev) << endl;

    codes.pop();
  }
  if (output_bit_count % 8) {
    output.write((char *)&prev, 1);
  }
}

// Обчислює мінімальну кількість біт для запису коду
int EncoderLZW::count_min_bits(int code) {
  for (int i = BITS; i >= 8; i--) {
    if ((1 << i) & code) {
      return i + 1;
    }
  }
  return 8;
}
