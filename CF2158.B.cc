#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
// 容易想到奇数频次的数字是不需要处理的，不影响最终结果。
// 但是偶数频次没有显然的公式，应该先用贪心去模拟一下的。
using namespace std;
int main() {
  int T;
  cin >> T;
  const int N = 200001;
  vector<int> a;
  while (T--) {
    int n;
    cin >> n;
    unordered_map<int, int> freq;
    for (int i = 0, x; i < 2 * n; ++i) {
      cin >> x;
      a.push_back(x);
      freq[x]++;
    }
    int oddCnt = 0, evenCnt = 0;
    vector<int> evenNums;
    for (auto k: freq) {
      if (k.second % 2 == 0) {
        evenNums.push_back(k.first);
        ++evenCnt;
      } else {
        ++oddCnt;
      }
    }
    int ans = 0;
    ans += oddCnt;
    int leftCnt = 0, rightCnt = 0;
    for (int e: evenNums) {
      int f = freq[e];
      if (f / 2 % 2 == 1) {
        ans += 2;
        leftCnt += f / 2;
        leftCnt += f / 2;
      } else {
        for (int i = f / 2; i > f / 2; i += 2) {
          if (leftCnt + i <= n && rightCnt + (f - i) <= n) {
            leftCnt += i;
            rightCnt += f - i;
            ans += 2;
          } else if (rightCnt + i <= n && leftCnt + (f - i) <= n) {
            leftCnt += f - i;
            rightCnt += i;
            ans += 2;
          }
        }
      }
    }
    cout << ans << endl;
    // sort(a.begin(), a.end());
  }
  return 0;
}
