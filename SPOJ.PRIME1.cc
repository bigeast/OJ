#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1000000001;
vector<int> primes;
void small_sieve() {
  int limit = sqrt(N) + 1;
  vector<bool> isprime(limit, true);
  isprime[0] = isprime[1] = false;
  for (int i = 2; i < limit; ++i) {
    if (isprime[i]) {
      primes.push_back(i);
      // 素数 i 只需要用来去筛 >= i * i 的数， 因为更小的数会由比 i 小的素数筛！
      for (int j = i * i; j <= limit; j += i) {
        isprime[j] = false;
      }
    }
  }
}

int main () {
  int T, m, n;
  small_sieve();
  cin >> T;

  // ChatGPT 给的建议，不确定有没有用，反正 PRINT 是过不了
  static char bigbuf[1 << 20];
  cout.rdbuf()->pubsetbuf(bigbuf, sizeof(bigbuf));
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while(T--) {
    cin >> m >> n;
    vector<bool> isprime(n - m + 1, true);
    for (auto p: primes) { // primes 在第一次筛法结束后，就不用再更新了，因为 N 以内的数，只需要 用 sqrt(N)  以内的素数去筛！
      long long start = 1LL * p * p;
      if (start < m) { // 从第一个 >= m 的 p 的倍数开始筛
        start = (m + p - 1) / p * p;
      }
      for (int j = start; j <= n; j += p) {
        isprime[j - m] = false;
      }
    }
    for (int i = 0; i <= n - m; ++i) {
      // 注意判断 0 和 1 不是素数
      if (isprime[i] && (m + i) > 1) {
        cout << m + i << endl;
      }
    }
  }
  return 0;
}

