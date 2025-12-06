#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
要点：
SPOJ 的输入更接近现实情况，每次只读取一个字符，能直观体会到 KMP 算法的特点。
getchar() 读取一个字符，会把上一行的换行符也读进来，因此要多加一句略过换行符。在每次 i++ 的地方都 getchar() 一下模拟输入。
为了找到所有匹配，最关键的是，一旦找到匹配，记录后继续让 j = next[j - 1] （假装没有匹配继续找）。
*/
void getNext(vector<int>& next, string& s) {
  next[0] = 0;
  for (int i = 1, j = 0; i < s.size(); ++i) {
    while (j > 0 && s[i] != s[j]) {
      j = next[j - 1];
    }
    if (s[i] == s[j]) ++j;
    next[i] = j;
  }
}
int main() {
  int n;
  string s;
  while (cin >> n) {
    cin >> s;
    vector<int> next(n, 0);
    vector<int> res;
    getNext(next, s);
    char c;
    int i = 0, j = 0;
    getchar();
    c = getchar();
    while (c != '\n') {
      if (s[j] == c) {
        c = getchar(); ++i;
        ++j;
      } else {
        if (j > 0) {
          j = next[j - 1];
        } else {
          c = getchar(); ++i;
        }
      }
      if (j == s.size()) {
        res.push_back(i - j);
        j = next[j - 1];
      }
    }
    for (int i = 0; i < res.size(); ++i) {
      cout << res[i] << endl;
    }
    if (res.size() == 0) {
      cout << endl;
    }
  }
  return 0;
}
