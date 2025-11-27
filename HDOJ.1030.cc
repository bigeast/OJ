#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int M, N;
pair<int, int> coor(int n) {
  int r = sqrt(n);
  if (n == r * r) {
    int r1 = sqrt(n - 1);
    return {r, n - r1 * r1};
  }
  return {r + 1, n - r * r};
}

unordered_map<int, bool> visited;
int steps = 0;
void bfs() {
  pair<int, int> pm = coor(M), pn = coor(N);
  queue<int> Q;
  Q.push(M);
  bool flag = false;
  int curr, row, col;
  while(!Q.empty()) {
    int t = Q.size();
    while(t--) {
      if (flag) break;
      curr = Q.front();
      Q.pop();
      pair<int, int> p = coor(curr);
      row = p.first;
      col = p.second;
      vector<int> next;
      if (col == 1) { // first
        next.push_back(curr + 1);
        next.push_back(curr + 2 * row);
      } else if (col == 2 * row - 1) { // last
        next.push_back(curr - 1);
        next.push_back(curr + 2 * row);
      } else {
        if (col % 2 == 1) {
          next.push_back(curr - 1);
          next.push_back(curr + 1);
          next.push_back(curr + 2 * row);
        } else {
          next.push_back(curr - 1);
          next.push_back(curr + 1);
        }
      }

      for (auto num: next) {
        if (visited.count(num)) continue;
        if (num == N) {
          cout << steps + 1 << endl;
          flag = true;
          break;
        }
        Q.push(num);
        visited[num] = true;
      }
    }
    ++steps;
  }
}
int main() {
  cin >> M >> N;
  if (M > N) swap(M, N);
  bfs();
}
