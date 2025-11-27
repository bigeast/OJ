#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

// 虽然很简单，但还是有些东西
// C++中的分割字符串，自己写总是很麻烦，直接找了一个模板。
// getchar() 很妙，哈哈哈
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
int main() {
  int n;
  string line;
  cin >> n;
  getchar();
  while(n--) {
    getline(cin, line);
    reverse(line.begin(), line.end());
    vector<string> words = split(line, ' ');
    reverse(words.begin(), words.end());
    for (int i = 0; i < words.size(); ++i) {
      cout << words[i];
      if (i == words.size() - 1) {
        cout << endl;
      } else {
        cout << " ";
      }
    }
  }
  return 0;
}
