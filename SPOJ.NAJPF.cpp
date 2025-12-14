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
      while (j > 0 && s[i] != s[j]) {
        j = next[j - 1];
      }
      if (s[i] == s[j]) ++j;
      next[i] = j;
    }
    int i = 0, j = 0;
    vector<int> res;
    while (i < s.size()) {
      if (s[i] == p[j]) {
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
        res.push_back(i - j + 1);
        j = next[j - 1];
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
