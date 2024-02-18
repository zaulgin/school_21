#include <stdio.h>

int fib(int n);

int main() {
  int a;
  char c;
  printf("Введите натуральное число:\n");
  scanf("%d%c", &a, &c);
  if (c != '\n' || a <= 0) {
    printf("n/a\n");
  } else {
    printf("%d\n", fib(a));
  }
  return 0;
}

int fib(int n) {
  if (n == 1 || n == 2) {
    return 1;
  }
  if (n == 0) {
    return 0;
  }
  return fib(n - 1) + fib(n - 2);
}
