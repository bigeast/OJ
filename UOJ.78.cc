#include <iostream>
#include <algorithm>
#include <vector>

// 二分图最大匹配模板题
// https://uoj.ac/problem/78
// 先把模板记住吧，慢慢理解。现在差不多理解了70%。
// 这个 UOJ 挺好用啊，可以看到测试样例！速度也很快，比传统的 OJ 好用。。
using namespace std;
const int N = 501;
vector<int> adj[N]; // 左侧节点邻接矩阵
int match[N]; // 右侧节点当前匹配到的左侧节点序号
int match_inv[N];
bool visited[N]; // 右侧节点是否被访问过
int dfs(int u) {
  for (int v: adj[u]) {
    if (!visited[v]) {
      visited[v] = true;
      if (match[v] == 0 || dfs(match[v])) {
        match[v] = u;
        match_inv[u] = v;
        return true;
      }
    }
  }
  return false;
}
int main() {
  int nl, nr, m;
  cin >> nl >> nr >> m;
  int x, y;
  while(m--) {
    cin >> x >> y;
    adj[x].push_back(y);
  }
  int res = 0;
  fill(match, match + N, 0);
  for (int i = 1; i <= nl; ++i) {
    if (adj[i].size() == 0) continue;
    fill(visited, visited + N, false);
    if (dfs(i)) {
      res++;
    }
  }
  cout << res << endl;
  for (int i = 1; i < nl; ++i) {
    cout << match_inv[i] << " ";
  }
  cout << match_inv[nl] << endl;
  return 0;
}
