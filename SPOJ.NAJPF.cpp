// Problem: Pattern Find
// Contest: SPOJ - Classical
// URL: https://www.spoj.com/problems/NAJPF/
// Memory Limit: 1536 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    string s, p;
    cin >> s >> p;
    vector<int> next(p.size());
    next[0] = 0;
    for (int i = 1, j = 0; i < p.size(); ++i) {
      while (j > 0 && p[i] != p[j]) {  // 求next数组可以理解为模式串与自身做匹配
        j = next[j - 1];
      }
      if (p[i] == p[j]) ++j;
      next[i] = j;
      // 下标i是单调递增的，且next[i]只依赖于前面已经计算出来的next值，相当于一种特殊的动态规划
    }
    int i = 0, j = 0;
    vector<int> res;
    while (i < s.size()) {
      if (s[i] == p[j]) {
        // 这里开始写错了，跟next一样自己跟自己去比了，易错点。
        ++i;
        ++j;
      } else {
        if (j > 0) {
          j = next[j - 1];
        } else {
          ++i;
        }
      }
      if (j == p.size()) {
        res.push_back(i - j + 1);  // 题目要求下标从1开始
        j = next[j - 1];  // 假装还没找到匹配（其实是继续找下一个匹配:D）
      }
    }
    if (res.size() == 0) {
      cout << "Not Found" << '\n';
    } else {
      cout << res.size() << '\n';
      for (int i = 0; i < res.size() - 1; ++i) {
        cout << res[i] << ' ';
      }
      cout << res.back() << '\n';
    }

    if (T) cout << endl;
  }
  return 0;
}
