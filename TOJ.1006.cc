#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; 
// 昨天第一次看到以为是二分图，ChatGPT 甚至给了我一个最大匹配的匈牙利算法。
// 我心想这也不是最大匹配啊。但是又很奇怪。搜了题解也没解释清楚。这也不是二分图检测。
// 今天用贪心做了一下，跟 DFS 不沾边。
// 思路是，依次给没被染色的顶点染色A，然后将其所有好友都染成另外一个颜色B。 这样在这一步被染色的顶点都是符合题目要求的。
// 如果后面碰到顶点发现已经被染色，那就不用管，它已经符合要求了。 即使它没有将它的任何好友染色也没关系。
// 由于题目保证了没有孤立顶点，那么这样遍历之后，所有点都会被染色，而且在另外一组有朋友。
const int N = 101;
int n;
vector<int> adj[N];
int main() {
  int n, a;
  cin >> n;
  int idx = 1;
  while(cin >> a) {
    if (a == 0) {
      ++idx;
      if (idx > n) break;
    } else {
      adj[idx].push_back(a);
    }
  }
  vector<int> color(N, -1);
  for (int i = 1; i <= n; ++i) {
    if (color[i] == -1) {
      color[i] = 0;
      for (int j = 0; j < adj[i].size(); ++j) {
        if (color[adj[i][j]] == -1) {
          color[adj[i][j]] = 1;
        }
      }
    }
  }
  vector<int> ans;
  for (int i = 1; i <= n; ++i) {
    if (color[i] == 0) {
      ans.push_back(i);
    }
  }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size() - 1; ++i) {
    cout << ans[i] << " ";
  }
  cout << ans[ans.size() - 1] << endl;
  return 0;
}
