#include <iostream>
#include <queue>
using namespace std;
const int MAX_LEN = 100001;
vector<bool> visited(MAX_LEN, false);
int depth = 0;
int n, k;
int bfs() {
  queue<int> Q;
  Q.push(n);
  visited[n] = true;
  while(!Q.empty()) {
    int t = Q.size();
    while(t--) {
      int curr = Q.front();
      Q.pop();
      if (curr == k) {
        return depth;
      }
      if(2 * curr < MAX_LEN && !visited[2 * curr]) {
        Q.push(2 * curr);
        visited[2 * curr] = true;
      }
      if(curr + 1 < MAX_LEN && !visited[curr + 1]) {
        Q.push(curr + 1);
        visited[curr + 1] = true;
      }
      if(curr - 1 >= 0 && !visited[curr - 1]) { //  第一次提交边界条件搞错了
        Q.push(curr - 1);
        visited[curr - 1] = true;
      }
    }
    ++depth;
  }
  return 0;
}
int main() {
  cin >> n >> k;
  cout << bfs() << endl;
}
