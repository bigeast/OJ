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

int manhattan(int a, int b) {
  pair<int, int> pa = coor(a), pb = coor(b);
  return abs(pa.first - pb.first) + abs(pa.second - pb.second);
}
unordered_map<int, bool> visited;
int bfs() {
  queue<int> Q;
  Q.push(M);
  visited.clear();
  visited[M] = true;
  int steps = 0;
  int curr, row, col;
  int minCost = manhattan(M, N);
  while(!Q.empty()) {
    int t = Q.size();
    // cout << t << endl;
    while(t--) {
      curr = Q.front();
      Q.pop();
      pair<int, int> p = coor(curr);
      row = p.first;
      col = p.second;
      cout << steps << " " << curr << " (" << row << "," << col << ") " << endl;
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
        // if (manhattan(num, N) >= minCost) continue;
        if (num == N) {
          return steps + 1;
        }
        Q.push(num);
        visited[num] = true;
      }
    }
    ++steps;
  }
  return 0;
}
int main() {
  cin >> M >> N;
  if (M > N) swap(M, N);
  int steps = bfs();
  cout << steps  << endl;
}
