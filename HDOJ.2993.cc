#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <algorithm>
using namespace std;

// 本来以为只是卡 IO，没想到题目没理解对，不是 k 是最大为 k，所以算法复杂度是 N^2 的，看网上说需要斜率优化 DP，又是第一次听说。
const int N = 100001;
const int BUFF_SIZE = 5 * N;
long long numsum[N];
inline int readIntManual(const char*& ptr) {
    int value = 0;
    // 跳过空格
    while (*ptr && (*ptr == ' ' || *ptr == '\n' || *ptr == '\r')) {
        ptr++;
    }
    // 解析数字
    while (*ptr >= '0' && *ptr <= '9') {
        value = value * 10 + (*ptr - '0');
        ptr++;
    }
    return value;
}
int main() {
  int n, k;
  int a;
  string str;
  while(getline(cin, str)) {
    const char* p = str.c_str();
    n = readIntManual(p);
    k = readIntManual(p);
    numsum[0] = 0;
    long long ans = 0;
    if (n == 0 || k == 0) {
      continue;
    }
    getline(cin, str);
    p = str.c_str();
    for (int i = 0; i < n; ++i) {
      a = readIntManual(p);
      numsum[i + 1] = a + numsum[i];
      if (i >= k - 1)  {
        // ans = max(ans, numsum[i + 1] - numsum[i + 1 - k]);
        long long current_sum = numsum[i + 1] - numsum[i + 1 - k];
        ans = (current_sum > ans) ? current_sum : ans; 
      }
    }
    printf("%.2f\n", ((double) ans) / k);
  }
  return 0;
}
