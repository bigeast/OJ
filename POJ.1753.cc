#include <iostream>
#include <queue>
#include <vector>
using namespace std;
char board[5][5];
vector<bool> visit(1<<16, false);
int start = 0;
int steps = 0;
int f[16];
bool flag = false;
inline bool isInMaze(int x, int y) {
  return x >= 0 && x < 4 && y >= 0 && y < 4;
}
void initMask() {
  int dirs[5][2] = {{0,0},{1,0},{-1,0},{0,1},{0,-1}};
  int x, y;
  memset(f, 0, sizeof(f));
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int d = 0; d < 5; ++d) {
        x = i + dirs[d][0];
        y = j + dirs[d][1];
        if (isInMaze(x, y)) {
          f[4 * i + j] |= (1 << (15 - (4 * x + y)));
        }
      }
    }
  }
}
bool bfs() {
  queue<int> Q;
  Q.push(start);
  visit[start] = true;
  while(!Q.empty()) {
    int t = Q.size();
    while(t--) {
      int a = Q.front(), b;
      Q.pop();
      if (flag) return true;
      if (a == 0 || a == ((1<<16) - 1)) {
        flag = true;
        return true;
      }
      for (int i = 0; i < 16; ++i) {
        b = a ^ f[i];
        if (visit[b]) continue;
        visit[b] = true;
        Q.push(b);
      }
    }
    steps++;
  }
  return false;
}
int main() {
  start = 0;
  for (int i = 0; i < 4; ++i) {
    cin >> board[i];
    for (int j = 0; j < 4; ++j) {
      if (board[i][j] == 'b') {
        start |= (1 << (15 - (4 * i + j)));
      }
    }
  }
  initMask();
  if (bfs()) {
    cout << steps << endl;
  } else {
    cout << "Impossible" << endl;
  }
  return 0;
}
