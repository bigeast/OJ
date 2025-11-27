#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;
// 大数乘法，找到了一个很直观的模板，不需要从个位计算然后逆序。
// 看到这个测试样例我感到有些眼熟，想起来 POJ 上也有这个题，好像是 1005，记得当时盯着做了好久。
// 这次卡点是 10.0 3 这种数据，输出结果中的 .000 没有去掉。
// 00.33 这种数据也考虑一下。
string bigMul(string& a, string& b) {
  string res;
  vector<int> c(a.size() + b.size() - 1, 0);
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      c[i + j] += (a[i] - '0') * (b[j] - '0');
    }
  }

  for (int i = c.size() - 1; i > 0; --i) {
    c[i - 1] += c[i] / 10;
    c[i] = (c[i] % 10);
  }
  while(c[0]) {
    res.insert(res.begin(), (c[0] % 10) + '0');
    c[0] /= 10;
  }
  for (int i = 1; i < c.size(); ++i) {
    res += c[i] + '0';
  }
  return res;
}
string fastPow(string &a, int n) {
  if (n == 1) {
    return a;
  }
  string c = fastPow(a, n / 2);
  string cc = bigMul(c, c);
  if (n % 2) {
    cc = bigMul(cc, a);
  }
  return cc;
}
inline void rmTailingZero(string &a) {
  while(a[a.size() - 1] == '0') {
    a.erase(a.size() - 1, 1);
  }
}
inline void rmLeadingZero(string &a) {
  while(a[0] == '0') {
    a.erase(0, 1);
  }
}
int main() {
  string R;
  int n;
  while(cin >> R >> n) {
    string a = "";
    int p = 0;
    rmLeadingZero(R);
    for (int i = 0; i < R.size(); ++i) {
      if(R[i]!='.') {
        a += R[i];
      } else {
        p = R.size() - i - 1;
      }
    }
    string res;
    if (n == 0) {
      res = "1";
    } else {
      res = fastPow(a, n);
    }
    if (p > 0) {
      if (res.size() < p*n) {
        res.insert(0, p*n - res.size(), '0');
      }
      res.insert(res.size() - p*n, 1, '.');
      rmTailingZero(res);
    }
    if (res[res.size() - 1] == '.') {
      res.erase(res.size() - 1, 1);
    }
    cout << res << endl;
  }
}
