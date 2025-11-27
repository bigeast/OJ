#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
// POJ 的 C++ 标准比较老，不支持 auto 类型推断
// 第一次 TLE 是由于没有处理输入等于 0
const int N = 201;
bool visited[N];
class Seq {
  public:
    Seq(int r, string s): r(r), str(s) {}
    int r;
    string str;
};
int bfs(int n) {
    memset(visited, 0, sizeof(visited));
    queue<Seq> Q;
    Q.push({1, "1"});
    visited[1] = true;
    int flag = false;
    while(!Q.empty()) {
      if (flag) break;
      Seq& curr = Q.front();
      for (int r = 0, next_r; r < 2; ++r) {
        next_r = (10 * curr.r + r) % n;
        if (visited[next_r]) continue;
        string next_str(curr.str + (char)(r + '0'));
        Q.push({next_r, next_str});
        if (next_r == 0) {
          flag = true;
          cout << next_str << endl;
          break;
        }
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
