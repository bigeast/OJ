#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
const int N = 12;
const double EPS = 1e-10;

unordered_map<char, pair<int, int>> dirDict = {
  {'S', {1, 0}},
  {'W', {0, 1}},
  {'E', {1, 1}},
};
unordered_map<char, pair<double, double>> harmWt = {
  {'S', {0.5, 0.5}},
  {'W', {0.8, 0.2}},
  {'E', {0.2, 0.8}},
};
class Student {
  public:
    double genuine, power, health;
    double wg, wp;
    int x, y;
    int dx, dy;
    int op; // 是否反向 1, -1
    char group;
    Student(char group, int x, int y, double g, double p, double h):
      group(group), x(x), y(y), genuine(g), power(p), health(h), op(1) {
        dx = dirDict[group].first;
        dy = dirDict[group].second;
        wg = harmWt[group].first;
        wp = harmWt[group].second;
    }

    inline int getHarm() {
      if (health < EPS) return 0;
      return (int) ((wg * genuine + wp * power) * (health + 10) / 100);
    }

    void forward() {
      int xx = x + op * dx;
      int yy = y + op * dy;
      if (xx < 1 || xx > N || yy < 1 || yy > N) {
        op *= -1;
        xx = x + op * dx;
        yy = y + op * dy;
        if (xx < 1 || xx > N || yy < 1 || yy > N) { // 容易错
          xx = x;
          yy = y;
        }
      }
      x = xx;
      y = yy;
    }
};

int main() {
  int T;
  cin >> T;
  while(T--) {
    int steps; cin >> steps; char s; 
    vector<Student*> handle[15][15];
    vector<Student*> allStu;
    while(cin >> s) {
      if (s == '0') break;
      int x, y;
      double g,p,h;
      cin >> x >> y >> g >> p >> h;
      Student *stu = new Student(s, x, y, g, p, h);
      handle[x][y].push_back(stu);
      allStu.push_back(stu);
    }
    while(steps--) {
      for(int i = 1; i <= 12; ++i) {
        for(int j = 1; j <= 12; ++j) {
          if(handle[i][j].size() == 2) {
            Student *s0 = handle[i][j][0];
            Student *s1 = handle[i][j][1];
            if (s0->group != s1->group) { // 互相伤害
              double harm0 = s0->getHarm();
              double harm1 = s1->getHarm();
              s0->health -= harm1;
              s1->health -= harm0;
            }
          }
          handle[i][j].clear();
        }
      }
      for (auto stu: allStu) {
        if (stu == NULL) continue;
        if (stu->health > EPS) {
          stu->forward();
          handle[stu->x][stu->y].push_back(stu);
        }
        // delete stu 这里为啥错？
      }
    }
    
    unordered_map<char, int> summaryCnt;
    unordered_map<char, int> summaryHealth;
    for(int i = 1; i <= 12; ++i) {
      for(int j = 1; j <= 12; ++j) {
        for(auto stu: handle[i][j]) {
          summaryCnt[stu->group]++;
          summaryHealth[stu->group] += stu->health;
        }
      }
    }
    cout << summaryCnt['S'] << " " << summaryHealth['S'] << endl;
    cout << summaryCnt['W'] << " " << summaryHealth['W'] << endl;
    cout << summaryCnt['E'] << " " << summaryHealth['E'] << endl;
    cout << "***" << endl;
  }
  return 0;
}
