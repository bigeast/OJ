#include <iostream>
using namespace std;

inline int builtin(uint32_t x) { return __builtin_popcount(x); }

inline int brian(uint32_t x) {
  int c = 0;
  while (x) {
    x &= x - 1;
    c++;
  }
  return c;
}

inline int loop32(uint32_t x) {
  int c = 0;
  for (int i = 0; i < 32; i++) {
    c += (x >> i) & 1;
  }
  return c;
}

// SWAR popcount
inline int bit_trick(uint32_t v) {
  v = v - ((v >> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
  return (((v + (v >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
}

uint32_t a[100000000];

template <class F>
double run(F f) {
  auto start = chrono::high_resolution_clock::now();
  volatile int s = 0;
  for (int i = 0; i < 100000000; i++) s += f(a[i]);
  auto end = chrono::high_resolution_clock::now();
  return chrono::duration<double>(end - start).count();
}

int main() {
  srand(1);
  for (int i = 0; i < 100000000; i++) a[i] = rand();

  cout << "builtin:    " << run(builtin) << " sec\n";
  cout << "brian:      " << run(brian) << " sec\n";
  cout << "bit_trick:  " << run(bit_trick) << " sec\n";
  cout << "loop32:     " << run(loop32) << " sec\n";
}
/*
不开优化
builtin:    0.350714 sec
brian:      4.2851 sec
bit_trick:  0.445498 sec
loop32:     6.72118 sec

-O2 优化
builtin:    0.177727 sec
brian:      1.62325 sec
bit_trick:  0.189276 sec
loop32:     0.940725 sec
*/

