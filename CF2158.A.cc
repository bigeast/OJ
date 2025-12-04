#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, y, r;
    cin >> n;
    cin >> y >> r;
    cout << ((y/2+r) > n ? n : y/2+r) << endl;
  }
  return 0;
}
