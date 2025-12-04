#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
  int n = 0, x = 0, y = 0;
  scanf("%x,%d,%d", &n, &x, &y);
  if (n & (1<<x)) {
    n -= (1<<x);
  }
  unsigned int mask = -1;
  mask -= 7<<(y-2);
  n &= mask;
  n += 6<<(y-2);
  printf("%x\n", n);
  return 0;
}
