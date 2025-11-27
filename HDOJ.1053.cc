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

class Node {
  public:
    int val;
    char chr = 0;
    Node *left, *right;
    Node(): val(0), left(nullptr), right(nullptr) {}
    Node(int val, Node *left, Node *right): val(val), left(left), right(right) {}
    Node(int val, char chr): val(val), chr(chr), left(nullptr), right(nullptr) {}
    struct Compare {
      bool operator() (const Node *a, const Node *b) {
        return a->val > b->val;
      }
    };
};
void dfs(Node* r, int depth, unordered_map<char, int>& codeLen) {
  if (r == nullptr) return ;
  if (r->left == nullptr && r->right == nullptr) {
    codeLen[r->chr] = depth;
  }
  dfs(r->left, depth + 1, codeLen);
  dfs(r->right, depth + 1, codeLen);
}
int main() {
  string str;
  while(cin >> str && str != "END") {
    unordered_map<char, int> freq;
    for (char c: str) {
      freq[c]++;
    }
    priority_queue<Node*, vector<Node*>, Node::Compare> Q;
    vector<Node> nodes;
    nodes.reserve(100000); // 牛逼，值了。用 vector 存储 Node 是不安全的，因为底层会重新分配内存，导致野指针！
    int idx = 0;
    for (auto const& kv: freq) {
      // cout << kv.first << " " << kv.second << endl;
      nodes.emplace_back(kv.second, kv.first);
      Q.push(&nodes[idx++]);
    }
    while (Q.size() > 1) {
      Node* a = Q.top();
      Q.pop();
      Node* b = Q.top();
      Q.pop();
      // cout << " a " << a->val << " b " << b->val << endl;
      nodes.emplace_back(a->val + b->val, a, b);
      Q.push(&nodes[idx++]);
    }
    unordered_map<char, int> codeLen;
    Node *r = Q.top();
    dfs(r, 0, codeLen);

    int totalLen = 0;
    for (auto const& kv: codeLen) {
      // cout << kv.first << " freq: " << freq[kv.first] << " len: " << kv.second << endl;
      totalLen += kv.second * freq[kv.first];
    }
    printf("%d %d %.1f\n", (int) str.size() * 8, totalLen, str.size() * 8.0 / totalLen);
  }
  return 0;
}
