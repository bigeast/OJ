#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
// POJ 的 C++ 标准比较老，不支持 auto 类型推断
// 第一次 TLE 是由于没有处理输入等于 0
// TLE 是由于每一步都存储了完整路径，导致了很多不必要的字符串拷贝
// 使用路径恢复就可以解决。
const int N = 201;
bool visited[N];
int pre[N];
char digit[N];
int bfs(int n) {
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    Q.push(1);
    visited[1] = true;
    bool flag = false;
    pre[1] = -1;
    digit[1] = '1';
    while(!Q.empty()) {
      int curr = Q.front();
      for (int r = 0, next_r; r < 2; ++r) {
        next_r = (10 * curr + r) % n;
        if (visited[next_r]) continue;
        pre[next_r] = curr;
        digit[next_r] = '0' + r;
        if (next_r == 0) {
          flag = true;
          break;
        }
        visited[next_r] = true;
        Q.push(next_r);
      }
      if (flag) {
        int p = 0;
        string res = "";
        while(p > -1) {
          res += digit[p];
          p = pre[p];
        }
        reverse(res.begin(), res.end());
        cout << res << endl;
        break;
      }
      Q.pop();
    }
    return 0;
}
int main() {
  int n;
  while(cin >> n) {
    if (n == 0) break;
    bfs(n);
  }
  return 0;
}
