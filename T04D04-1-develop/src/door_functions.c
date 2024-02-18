#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846

void verAn(double x) { printf("%.7lf|", (1 / (1 + pow(x, 2)))); }

void lemBer(double x) {
  if ((sqrt(1 + pow(x, 2)) - pow(x, 2) - 1) < 0) {
    printf("-|");
  } else {
    printf("%.7lf|", sqrt(sqrt(1 + 4 * pow(x, 2)) - pow(x, 2) - 1));
  }
}

void quadHip(double x) {
  if (x == 0) {
    printf("-|");
  } else {
    printf("%.7lf|", (1 / pow(x, 2)));
  }
}

int main() {
  for (double i = -M_PI; i <= M_PI; i += 2 * M_PI / 41.) {
    printf("%.7lf|", i);
    verAn(i);
    lemBer(i);
    quadHip(i);
    printf("\n");
  }
  return 0;
}
