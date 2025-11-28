#include <iostream>
#include <sstream> // 引入 stringstream 头文件
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
#include <algorithm>

// 应该做了有两个半小时，心路历程很复杂。
// 开始得到字符表示看上去是对的，很高兴，以为难点在反解。
// 实际反解倒是很简单的。WA之后才注意到多了一行逗号,
// 感觉这个很像读研时搞的编解码匹配，编解码不匹配的恐惧支配的回忆侵袭了我。
// 一直在想题目是根据什么规则，少加了一个逗号。尝试了几种办法，都不太行。
// 最后发现，是直接把最后一行设置成点号，覆盖了逗号。我一直以为点号是新加的。。
// 而且题目完全没说图的大小，只能往大了设了。（结果发现 N=101 就能过）
using namespace std; 
const int N = 10001;
int image[N][N];
bool visited[N][N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
char dirCode[5] = "RTLB";
unordered_map<char, pair<int, int>> invCode = {
    {'R', {1,0}},
    {'T', {0,1}},
    {'L', {-1,0}},
    {'B', {0,-1}}
};

vector<string> bfs(int sx, int sy, int n) {
  vector<string> describs;
  queue<pair<int, int>> Q;
  Q.push({sx, sy});
  visited[sx][sy] = true;
  string desc;
  while(!Q.empty()) {
    pair<int, int> p = Q.front();
    Q.pop();
    desc.clear();
    for (int i = 0, xx, yy; i < 4; ++i) {
      xx = p.first + dirs[i][0];
      yy = p.second + dirs[i][1];
      if (xx > 0 && xx < N && yy > 0 && yy < N && image[xx][yy] == 1 && !visited[xx][yy]) {
        desc += dirCode[i];
        Q.push({xx, yy});
        visited[xx][yy] = true;
      }
    }
    desc += ',';
    describs.push_back(desc);
  }
  describs[describs.size() - 1] = ".";
  return describs;
}

vector<pair<int, int>> bfsInv(int sx, int sy,
    vector<string>& codingStr, vector<pair<int, int>>& blacks) {
  queue<pair<int, int>> Q;
  blacks.push_back({sx, sy});
  Q.push({sx, sy});
  int idx = 0;
  while(!Q.empty()) {
    pair<int, int> p = Q.front();
    Q.pop();
    string& desc = codingStr[idx++];
    int dx, dy;
    int x = p.first, y = p.second;
    for (char c: desc) {
      if (c == ',' || c == '.') break;
      dx = invCode[c].first;
      dy = invCode[c].second;
      Q.push({x + dx, y + dy});
      blacks.push_back({x + dx, y + dy});
    }
  }
  return blacks;
}

int main() {
  int n, x, y;
  string str;
  getline(cin, str);
  stringstream ss(str);
  if (str.find(' ') != string::npos) {
    ss >> x >> y;
    vector<string> codingStr;
    while(cin >> str) {
      codingStr.push_back(str);
      if (str == ".") break;
    }
    vector<pair<int, int>> blacks;
    bfsInv(x, y, codingStr, blacks);
    sort(blacks.begin(), blacks.end());
    cout << blacks.size() << endl;
    for (int i = 0; i < blacks.size(); ++i) {
      cout << blacks[i].first << " " << blacks[i].second << endl;
    }
  } else {
    ss >> n;
    int sx, sy;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      if (i == 0) {
        sx = x;
        sy = y;
      }
      image[x][y] = 1;
    }
    vector<string> codingStr = bfs(sx, sy, n);
    cout << sx << " " << sy << endl;
    for (auto& s: codingStr) {
      cout << s << endl;
    }
  }
  return 0;
}
