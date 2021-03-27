# op-lab4cpp
Лабораторна робота 4

## Варіант #0. Архіви

Завдання полягає в розробці простого архіватора. На вхід програми через параметри командного рядка подається ім'я вхідного та вихідного файлів та параметр, який вказує, що треба зробити – спакувати чи розпакувати вхідний файл. Алгоритм можете вибрати довільний, кілька алгоритмів є у посиланнях нижче. Наприклад, ви можете замінювати байти, що повторюються, на коротше представлення (run length encoding).

*Складніше завдання (+1 бал):* Створювати архів з кількох файлів та/або використати алгоритм стиснення Lempel—Ziv. Підійде будь-яка з версій алгоритму на ваш вибір. Найпростіша, на мою думку, LZW. 

Майте на увазі: LZ дуже простий алгоритм, складність у тому, що в цьому завданні ви матимете справу з великою кількість побітових операцій для роботи з числами, які мають 9, 10, 11 біт тощо, а не звичайними 8-, 16- і 32-бітними, до яких звикли. Вам може стати в нагоді ця книга: [Hacker's Delight](https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren/dp/0321842685) (переклад: [Алгоритмические трюки для програмистов](https://www.google.com/search?q=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5+%D1%82%D1%80%D1%8E%D0%BA%D0%B8+%D0%B4%D0%BB%D1%8F+%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2))

### Вхідні та вихідні дані
Для стискування на вхід подається один або кілька файлів у довільному форматі (ви не знаєте наперед, які файли стискатиме користувач), на виході отримуємо архів. Наприклад, якщо ваша програма компілюється в megazip.exe:
```
> megazip.exe --compress output.mgzip input.bmp
Compressing file input.bmp... Done.
Result written to output.mgzip

// Або якщо підтримується кілька файлів
> megazip.exe --compress output.mgzip input1.bmp input2.bmp input3.bmp
Compressing file input1.bmp... Done.
Compressing file input2.bmp... Done.
Compressing file input3.bmp... Done.
Result written to output.mgzip
```

Для розпаковування на вхід подається ім\'я вхідного файла. Ім\'я вихідних файлів зазвичай збережене всередині архіву.
```
> megazip.exe --decompress output.mgzip
Getting out file input1.bmp... Done.
Getting out file input2.bmp... Done.
Getting out file input3.bmp... Done.
3 files written.
```

### Посилання
* [Стиснення файлів](https://en.wikipedia.org/wiki/Lossless_compression)
* [Run length encoding](https://en.wikipedia.org/wiki/Run-length_encoding)
* [Lempel—Ziv](http://math.mit.edu/~goemans/18310S15/lempel-ziv-notes.pdf) (1 частина документа). Підійде будь-яка з версій алгоритму на ваш вибір. 
