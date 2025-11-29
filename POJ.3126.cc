#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring> // pit 4 memset
using namespace std;
const int N = 10000;

// 一道简简单单的 BFS 题目，本来是因为偶然看到觉得有意思才做的，结果给我整出来这么多 bug，得好好总结下
// 主要是这里不再是在图中搜索，不存在坐标问题，导致没有去写判断 valid 的条件，导致 RE 了很久。
// 还有就是 POJ 前天突然挂了，导致这道题也中断了，今天才好。
int n;
int start, target;
vector<bool> isprime(N, true);
bool visited[N];
// int pre[N];
void sieve() {
  isprime[0] = isprime[1] = false;
  for (int i = 2; i < sqrt(N) + 1; ++i) {
    if (isprime[i]) {
      for (int j = 2 * i; j < N; j += i) {
        isprime[j] = false;
      }
    }
  }
}

int bfs() {
  queue<int> Q;
  memset(visited, 0, sizeof(visited));
  Q.push(start);
  visited[start] = true;
  // pre[start] = -1;
  int depth = 0;
  if (start == target) { // pit 2 未考虑起始和结束相同的情况
    return 0;
  }
  while(!Q.empty()) {
    int t = Q.size();
    while(t--) {
      int curr = Q.front();
      Q.pop();
      for (int i = 0; i < 4; ++i) {
        int base = 1, digit = curr;
        for (int j = 0; j < i; ++j) {
          base *= 10;
          digit /= 10;
        }
        digit %= 10;
        int from = curr - digit * base;
        // if (i == 3) from += base; // pit 3 四位数限制，首位不能为 0
        for (int j = from; j <= from + 9 * base; j += base) { // pit 1 <=
          if (visited[j] || !isprime[j]) continue;
          if (j < 1000 || j > 9999) continue; // pit!!!!
          Q.push(j);
          visited[j] = true; // pit 5
          // pre[j] = curr;
          if (j == target) {
            /*
            int p = target;
            while(p > 0) {
              cout << p << endl;
              p = pre[p];
            }
            */
            return depth + 1;
          }
        }
      }
    }
    depth++;
  }
  depth = -1;
  return depth;
}

int main() {
  sieve();
  cin >> n;
  while(n--) {
    cin >> start >> target;
    int depth = bfs();
    if (depth < 0) cout << "Impossible" << endl;
    else {
      cout << depth << endl;
    }
  }
}
