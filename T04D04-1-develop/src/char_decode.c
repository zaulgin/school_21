#include <math.h>
#include <stdio.h>

// ***== Получен Quest 2. Создать программу src/char_decode.c, которая принимает
// в качестве параметра командной строки режим работы (0 — кодирование или 1 —
// декодирование). Если выбран режим декодирования, то программа должна
// принимать из stdin разделенные пробелом двухсимвольные строки и выдавать в
// stdout декодированные символы, разделенные также пробелом. При кодировании
// выполняется обратная операция. Подзадачи кодирования и декодирования должны
// быть выделены в отдельные функции. Обратить внимание на ASCII таблицу. В
// случае ошибки выводить «n/a». Признаком окончания ввода служит символ
// переноса строки ==***

// | Параметры командной строки | Входные данные | Выходные данные |
// | ------ | ------ | ------ |
// | 0 | W O R L D | 57 4F 52 4C 44 |
// | 0 | WORLD | n/a |
// | 1 | 48 45 4C 4C 4F | H E L L O |
// | 1 | 48454C4C4F | n/a |

int decoding();
int coding();

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("n/a\n");
    return 1;
  }

  if (*argv[1] == '1') {
    printf("Режим декодирования активирован, задайте двухсимвольные числа "
           "разделенные пробелом:\n");
    decoding();
  }

  if (*argv[1] == '0') {
    printf("Режим кодирования активирован, задайте символы разделенные "
           "пробелом:\n");
    coding();
  }
  return 0;
}

int decoding() {
  int i;
  char c;
  int res = scanf("%x%c", &i, &c);
  while (res == 2) {
    if (i < 32 || i > 127) {
      printf("n/a");
      break;
    } else {
      printf("%c ", i);
    }
    if (c == '\n') {
      break;
    }
    if (c != ' ') {
      printf("n/a");
      break;
    }
    res = scanf("%x%c", &i, &c);
  }
  printf("\n");
  return 0;
}

int coding() {
  char c, h;
  int res = scanf("%c%c", &c, &h);
  while (res == 2) {
    if (h != ' ' && h != '\n') {
      printf("n/a");
      break;
    }
    if (h == '\n') {
      printf("%X ", c);
      break;
    }
    printf("%X ", c);
    res = scanf("%c%c", &c, &h);
  }
  printf("\n");
  return 0;
}