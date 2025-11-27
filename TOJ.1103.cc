#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
using namespace std; 
const int N = 5000;
vector<vector<long long>> points(N, vector<long long>(2, 0));
vector<double> circleFromThreePoints(const vector<long long>& p1,
                                          const vector<long long>& p2,
                                          const vector<long long>& p3) {
    double x1 = p1[0], y1 = p1[1];
    double x2 = p2[0], y2 = p2[1];
    double x3 = p3[0], y3 = p3[1];

    double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

    if (fabsl(D) < 1e-18) {
        return {};   // 共线，无圆
    }

    double x1sq = x1 * x1 + y1 * y1;
    double x2sq = x2 * x2 + y2 * y2;
    double x3sq = x3 * x3 + y3 * y3;

    double xc = (x1sq * (y2 - y3) + x2sq * (y3 - y1) + x3sq * (y1 - y2)) / D;

    double yc = (x1sq * (x3 - x2) + x2sq * (x1 - x3) + x3sq * (x2 - x1)) / D;

    double r2 = (xc - x1) * (xc - x1) + (yc - y1) * (yc - y1);
    return {xc, yc, r2};
}
int main() {
  int n;
  int x, y;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> points[i][0] >> points[i][1];
  }
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, n-1);

  /*
  if ((n - 3) % 2 != 0) {
    cout << "No solution" << endl;
  }
  */
  int T = 10000;
  while(T--) {
    int i = dist(gen), j = dist(gen), k = dist(gen);
    if (i == j || j == k || i == k) continue;
    vector<double> circle = circleFromThreePoints(points[i], points[j], points[k]);
    if (circle.empty()) continue;
    double cx = circle[0], cy = circle[1], r2 = circle[2];
    int inCnt = 0;
    for (int p = 0; p < n; ++p) {
      if (p == i || p == j || p == k) continue;
      double x = points[p][0], y = points[p][1];
      if ((cx - x)*(cx - x) + (cy - y)*(cy - y) < r2) {
        ++inCnt;
      }
    }
    if (inCnt == (n - 3) / 2) {
      cout << points[i][0] << " " << points[i][1] << endl;
      cout << points[j][0] << " " << points[j][1] << endl;
      cout << points[k][0] << " " << points[k][1] << endl;
      return 0;
    }
  }
  cout << "No solution" << endl;
  return 0;
}
