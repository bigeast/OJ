#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
// 总结：
// 1. 使用前缀和进行优化，在实际操作插入和删除时，可以提前判断是否符合条件。
// 2. 边界条件太容易写错了，卡了好久。
// 3. string 插入和删除的操作不太一致。insert 需要迭代器，而 erase 需要下标。
using namespace std; 
int n;
const int N = 1000;
int main() {
  string str, ans;
  int nums = 0;
  int cntsum[N + 2];
  int subsum = 0;
  cin >> n;
  while(cin>>str) {
    vector<int> bitsIdx;
    memset(cntsum, 0, sizeof(0));
    subsum = 0;
    for (int i = 1; i <= str.size(); ++i) {
      if (str[i - 1] == '1') {
        cntsum[i] = i == 1 ? 1 : 1 + cntsum[i - 1];
        subsum += i;
        bitsIdx.push_back(i);
      } else {
        cntsum[i] = cntsum[i - 1];
      }
    }
    if (str.size() == n - 1) {
      for (int i = 0, newSub; i <= str.size(); ++i) { //  可插入位置比长度多 1
        // insert 0
        newSub = subsum + cntsum[str.size()] - cntsum[i];
        if (newSub % (n + 1) == 0) {
          str.insert(str.begin() + i, '0');
          break;
        } else if ((newSub + i + 1) % (n + 1) == 0) { // insert 1
          str.insert(str.begin() + i, '1');
          break;
        }
      }
    } else if (str.size() == n + 1) {
      for (int i = 1, newSub; i <= str.size(); ++i) {
        // delete 0
        newSub = subsum - (cntsum[str.size()] - cntsum[i]);
        // delete 1
        if (str[i - 1] == '1') {
          newSub -= i;
        }
        if (newSub % (n + 1) == 0) {
          str.erase(i - 1, 1);
          break;
        }
      }
    } else {
      if (subsum % (n + 1) != 0) {
        for (int pos: bitsIdx) {
          if ((subsum - pos) % (n + 1) == 0) {
            str[pos - 1] = '0';
            break;
          }
        }
      }
    }
    cout << str << endl;
  }
}
