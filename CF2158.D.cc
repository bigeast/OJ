#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
using namespace std;

// 思路很直观，但是实现很复杂，主要是担心 string 不断拷贝的性能问题，此时有些希望自己熟悉智能指针。
// 还有就是不确定是否需要用到 Manacher 算法，先问 Gemeni 要了个模板，顺便后面学习下吧。
// 回文串检测应该不需要每次都做，因为每次操作都是把回文串整体 flip，位置还是不变。
// 不过不确定若干次 flip 之后会不会出现新的回文串，貌似不会？

unordered_map<string, int> m;
int hashIdx = 0;

int n;
string a, b;
int hash(string& a) {
  if (m.count(a)) {
    return m[a];
  } else {
    m[a] = hashIdx++;
  }
}
// Manacher 算法模板
// 返回一个数组 P，其中 P[i] 表示以预处理字符串 T[i] 为中心的最长回文半径
vector<pair<int,int>> manacher(const string& s) {
    // 1. 预处理：插入特殊字符
    // 示例："aba" -> "^#a#b#a#$"
    string T = "^";
    for (char c : s) {
        T += "#";
        T += c;
    }
    T += "#$";

    vector<pair<int,int>> res;

    int n = T.length();
    // P[i] 存储以 T[i] 为中心的回文半径（不包含边界字符 # 或 ^/$）
    vector<int> P(n, 0); 
    
    // C: 当前最右回文串的中心
    // R: 当前最右回文串的右边界
    int C = 0, R = 0;

    // 2. 遍历预处理后的字符串
    for (int i = 1; i < n - 1; ++i) {
        // 计算 i'（i 关于 C 的对称点）
        int i_mirror = 2 * C - i; 

        // 利用对称性：如果 i 在 R 范围内，则 P[i] 至少等于 P[i'] 或 R-i 中的较小值
        if (R > i) {
            P[i] = min(R - i, P[i_mirror]);
        }

        // 尝试向外扩展，更新回文半径 P[i]
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
            P[i]++;
        }

        // 如果当前回文串的右边界超过 R，则更新 C 和 R
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    for (int i = 1; i < P.size() - 1; ++i) {
        // 只要半径 P[i] > 0，就存在一个回文串
        if (P[i] < 2) continue;

        int length = P[i];
        
        // 计算原始字符串 s 中的起始索引
        // i 是 T 中的中心索引。
        // 对于 T 中的奇数索引中心（#），起始索引为 (i - length) / 2
        // 对于 T 中的偶数索引中心（字符），起始索引为 (i - 1 - length) / 2
        // 实际上，(i - 1 - length) / 2 适用于两种情况。
        int start_index = (i - 1 - length) / 2;

        // 提取子串
        res.push_back({start_index, start_index + length - 1});
    }
    return res;
}
inline string
int bfs() {
  queue<int> Q;
  Q.push(a);
  while (!Q.empty()) {
    int t = Q.size();
    while(t--) {
      string curr = Q.front();
      Q.pop();
      vector<pair<int, int>> P = manacher(curr);
      for (auto& p: P) {
        string filpStr = curr.substr(p.first)
        string next = curr.substr(0, p.first) + curr.substr(p.first, p.second - p.first + 1) + curr.substr(p.second, curr.size() - p.second);
        Q.push(curr);
      }
    }
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    m.clear();
    hashIdx = 0;
    cin >> n;
    cin >> a >> b;
  }
  return 0;
}
