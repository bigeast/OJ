#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

// 时间复杂度 O(n^2)，由于题目规模是 N <= 1000，所以也能过。
// 有点想不起来最优算法了，好像是用优先级队列加速获取 j 的过程？
int main() {
  int n;
  const int N = 1001;
  int a[N];
  int f[N];
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    memset(f, 0, sizeof(f));
    f[0] = a[0];
    int ans = f[0];
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (a[j] < a[i]) {
          f[i] = max(f[i], f[j]);
        }
      }
      f[i] += a[i];
      ans = max(ans, f[i]);
    }
    cout << ans << endl;
  }
}
