#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <unordered_set>
using namespace std;
int N, M, T;
pair<int, int> S, D;
int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
char maze[10][10];
bool visit[10][10];
bool flag = false;
inline bool isInMaze(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < M;
}
// 对问题解空间大小严重低估，导致一开始就没有从剪枝角度思考。
// 犯的低级错误有：
//  1. 起始点没有设置为 visited
//  2. maze[xx][yy] != 'X' 写成 maze[x][y] != 'X'
//  3. dotCnt 统计错误，且剪枝条件 T > dotCnt + 1 开始搞成了 T > dotCnt
// 奇偶剪枝最关键，如果没发现会导致 TLE。其它剪枝属于锦上添花。
//
/* 1. 奇偶剪枝 | 842ms
 *  1.1 叠加 T - depth < manhaton | 873ms
 *  1.2 叠加 T - depth < manhaton && T > dotCnt + 1 | 686ms
 *  1.3 叠加 T - depth < manhaton && flag 提前退出 | 249ms
 *  1.4 叠加 flag 提前退出 | 249ms
 *  1.5 叠加 T > dotCnt + 1 | 670ms
 *  1.6 叠加 flag 提前退出 && T > dotCnt + 1 | 78ms
 */
void dfs(int x, int y, int depth) {
  if (depth == T && maze[x][y] == 'D') {
    flag = true;
    return ;
  }
  int manhaton = abs(D.first - x) + abs(D.second - y);
  if ((T - depth) % 2 != manhaton % 2) { // 不加这个剪枝会TLE
    return ;
  }
  if (T - depth < manhaton) {
    return ;
  }

  for (int i = 0, xx, yy; i < 4; ++i) {
    xx = x + dirs[i][0];
    yy = y + dirs[i][1];
    if (isInMaze(xx, yy) && !visit[xx][yy] && maze[xx][yy] != 'X') {
      if (flag) { // 提前退出
        continue; 
      }
      visit[xx][yy] = true;
      dfs(xx, yy, depth + 1);
      visit[xx][yy] = false;
    }
  }
  return ;
}
int main() {
  while(cin >> N >> M >> T) {
    if (N == 0 && M == 0 && T == 0) {
      return 0;
    }
    int dotCnt = 0;
    for (int i = 0; i < N; ++i) {
      cin >> maze[i];
      for (int j = 0; j < M; ++j) {
        if (maze[i][j] == 'S') {
          S = {i, j};
        } else if (maze[i][j] == 'D') {
          D = {i, j};
        } else if (maze[i][j] == '.') {
          ++dotCnt;
        }
      }
    }
    if (T > dotCnt + 1) { // T 不能超过空格个数
      cout << "NO" << endl;
      continue;
    }
    memset(visit, 0, sizeof(visit));
    flag = false;
    visit[S.first][S.second] = true;
    dfs(S.first, S.second, 0);
    cout << (flag ? "YES" : "NO") << endl;
  }
  return 0;
}

