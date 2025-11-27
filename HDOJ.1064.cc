#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
// 有点简单了
using namespace std;
int main() {
  double num;
  double ans = 0.0;
  for (int i = 0; i < 12; ++i) {
    cin >> num;
    ans += (int) (num * 100);
  }
  printf("$%.2f", ans / 1200);
  return 0;
}

