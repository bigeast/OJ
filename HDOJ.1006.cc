#include <iostream>
#include <cmath>
using namespace std;
double D;
inline bool isWithInD(double d1, double d2) {
  double d = abs(d1 - d2);
  return min(d, 360 - d) > D;
}
inline double getDegree(double accuD) {
  return accuD - (int) (accuD / 360) * 360;
}
int main() {
  double dsec, dmin, dhour;
  while(cin >> D) {
    if (fabs(D + 1) < 1e-7) break;
    int cnt = 0;
    double delta = 0.01;
    double deltaSec = 6.0 * delta, deltaMin = 0.1 * delta, deltaHour = 0.00833333 * delta;
    for (double sec = 0; sec < 12 * 60 * 60; sec += delta) {
      dsec += deltaSec;
      dmin += deltaMin;
      dhour += deltaHour;
      if (dsec > 360) dsec -= 360;
      if (dmin > 360) dmin -= 360;
      if (dhour > 360) dhour -= 360;
      // cout << dsec << " " << dmin << " " << dhour << endl;
      if (isWithInD(dsec, dmin) && isWithInD(dsec, dhour) && isWithInD(dmin, dhour)) {
        ++cnt;
      }
    }
    printf("%0.3f\n", 100 * cnt * delta / 12.0 / 60.0 / 60.0);
  }
  return 0;
}
