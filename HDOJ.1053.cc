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

// 内存管理真是门学问啊。
// 一开始是想避免入队出队时候 Node 的不必要拷贝，因此想用 emplace 函数入队，但是这样出队时，还是需要赋值给新的变量，并且合并成新的节点时，是需要指针指向被弹出的Node 对象的。
// 首先想到的是先开一个 Node 数组，然后队列存储的是 Node*，指向数组中的各个元素，这样的话，优先级队的定义比较复杂，需要用三个参数的声明，而且还需要自定义比较函数。
// 但是第一个坑就是，数组不能用 vector！因为 vector 是会重新分配内存的，本地运行时，也稳定复现了这个问题，学以致用啊哈哈
// 修改成普通数组，还是会 WA，调大数组大小，会 MLE。
// 那就用堆内存，一次性 new 一个 Node 数组出来，但是这样需要手动初始化， 用不到 Node  定义的构造函，代码不简洁。
// 最终还是用new，但是一次只 new 一个 Node，这样可以用到定义好的构造函数。
//
// 还有个坑，就是只有一个元素时，码长是 1 而不是 0, 需要特殊处理。
//
// 另外犯的错有，在构造函数的初始化列表里面，right(left)，这种 typo bug 真的很致命。
//
// AI 推荐的写法是用智能指针，move 语义，但是写起来太麻烦，不太适合做竞赛题。
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
    // vector<Node> nodes;
    // nodes.reserve(100000); // 牛逼，值了。用 vector 存储 Node 是不安全的，因为底层会重新分配内存，导致野指针！
    int idx = 0;
    for (auto const& kv: freq) {
      // cout << kv.first << " " << kv.second << endl;
      Node *node = new Node(kv.second, kv.first);
      Q.push(node);
    }
    while (Q.size() > 1) {
      Node* a = Q.top();
      Q.pop();
      Node* b = Q.top();
      Q.pop();
      // cout << " a " << a->val << " b " << b->val << endl;
      Node *node = new Node(a->val + b->val, a, b);
      Q.push(node);
    }
    unordered_map<char, int> codeLen;
    Node *r = Q.top();
    dfs(r, 0, codeLen);

    int totalLen = 0;
    for (auto const& kv: codeLen) {
      // cout << kv.first << " freq: " << freq[kv.first] << " len: " << kv.second << endl;
      totalLen += kv.second * freq[kv.first];
    }
    if (freq.size() == 1) {
      for (auto const& kv: freq) {
        totalLen = kv.second;
      }
    }
    printf("%d %d %.1f\n", (int) str.size() * 8, totalLen, str.size() * 8.0 / totalLen);
  }
  return 0;
}
