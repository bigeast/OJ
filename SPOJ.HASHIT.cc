#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
unordered_map<int, string> m;

int my_hash(string& str) {
  int h = 0;
  for (int i = 0; i < str.size(); ++i) {
    h += str[i] * (i + 1);
    h %= 101;
  }
  h *= 19;
  h %= 101;

  // cout<<" init hash " <<h<<endl;
  int hh = 0, first_available = -1;
  // 遍历碰撞 list 看是否已存在
  for (int j = 0; j <= 19; ++j) {
    hh = h + j * (j + 23);
    hh %= 101;
    if (m.count(hh)) {
      if (m[hh] == str) { // 已存在，返回哈希值
        //cout<<" find str " <<hh<<endl;
        return hh;
      }
    }
  }
  for (int j = 0; j <= 19; ++j) {
    hh = h + j * (j + 23);
    hh %= 101;
    if (!m.count(hh)) { // 第一个可用地址
      //cout<<" new addr " <<hh<<endl;
      return hh;
    }
  }
  return -1;
}

int main () {
  int T, n;
  string line, token;
  cin >> T;
  while(T--) {
    cin >> n;
    m.clear();
    for (int i = 0; i < n; ++i) {
      cin >> line;
      token = line.substr(4, line.size() - 4);
      if (token.size() == 0 || token[0] == ' ') token = "";
      int h = my_hash(token);
      // cout<<line[0]<<" "<< token << " " << h <<endl;
      if (line[0] == 'A') {
        m[h] = token;
      } else {
        m.erase(h);
      }
    }
    vector<pair<int, string>> vec(m.begin(), m.end());
    sort(vec.begin(), vec.end());
    
    cout << vec.size() << endl;
    for (auto &item: vec) {
      cout << item.first << ":" << item.second << endl;
    }
  }
  return 0;
}

