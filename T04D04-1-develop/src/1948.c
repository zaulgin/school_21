#include <math.h>
#include <stdio.h>

int isSimple(int x);
int maxSimpleDivisor(int a);

int main() {
  int a;
  printf("Введите целое число:\n");
  scanf("%d", &a);
  if (a == 1) {
    printf("n/a\n");
    return 0;
  }
  printf("%d\n", maxSimpleDivisor(a));
  return 0;
}

int maxSimpleDivisor(int a) {
  if (a < 0) {
    a *= -1;
  }
  int tmp = a, msd = 0;

  for (int i = 2; i <= a * 0.5;) {
    if (tmp - i > 0) {
      tmp -= i;
    } else {
      if (tmp - i == 0 && isSimple(i) == 1) {
        msd = i;
        i++;
        tmp = a;
      } else {
        i++;
        tmp = a;
      }
    }
  }
  if (msd == 0) {
    msd = a;
  }
  return msd;
}

int isSimple(int x) {
  int tmp = x;
  for (int i = 2; i <= sqrt(x);) {
    if (tmp - i > 0) {
      tmp -= i;
    } else {
      if (tmp - i == 0) {
        return 0;
      } else {
        i++;
        tmp = x;
      }
    }
  }
  return 1;
}
