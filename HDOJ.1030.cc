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

int M, N;
pair<int, int> coor(int n) {
  int r = sqrt(n);
  if (n == r * r) {
    int r1 = sqrt(n - 1);
    return {r, n - r1 * r1};
  }
  return {r + 1, n - r * r};
}

int getAnsFromUp(int xM, int yM, int xN, int yN) {
  // 正三角向下求两个交点，然后算曼哈顿距离
  // 经过 2 * (xN - xM) - 1 步，可到达第一个交点(xN, yM + 1)
  // (xM, yM) 本层共有 2*xM + 1 个元素，因此后面元素个数是 2*xM + 1 - yM
  // 平移到 xN 行，再补充一个三角，对称点后面元素个数是 2*xM + 2 - yM
  // 对称点为 (xN, 2*xN + 1 - (2*xM + 2 - yM)) = (xN, 2 *(xN - xM) + yM - 1)
  int dx = 2 * (xN - xM) - 1;
  int y1 = yM + 1;
  int y2 = 2 * (xN - xM) + yM - 1;
  int dy = min(abs(yN - y1), abs(yN - y2));
  return dx + dy;
}

int getAnsFromDown(int xM, int yM, int xN, int yN) {
  // 倒三角，可以转化为两个相邻的正三角之后，复用上面的公式，注意 dx 多走了一步要加 1
  int ans1 = getAnsFromUp(xM, yM - 1, xN, yN);
  int ans2 = getAnsFromUp(xM, yM + 1, xN, yN);
  return 1 + min(ans1, ans2);
}

int main() {
  cin >> M >> N;
  if (M > N) swap(M, N);
  auto [xM, yM] = coor(M);
  auto [xN, yN] = coor(N);
  // cout << xM << " " << yM << endl;
  // cout << xN << " " << yN << endl;
  int ans = 0;
  if (xM == xN) {
    ans = yN - yM;
  } else {
    int dx, dy;
    if (yM % 2 == 1) { // 正三角
      ans = 1 + getAnsFromDown(xM + 1, yM + 1, xN, yN);
    } else {
      // dx = 2 * (xN - xM)
      ans = getAnsFromDown(xM, yM, xN, yN);
      // cout << "dx " << dx << endl;
      // cout << "dy " << dy << endl;
      // cout << "y " << y1 << " " << y2 << " " << y3 << " " << y4 << endl;
    }
  }
  cout << ans << endl;
}
