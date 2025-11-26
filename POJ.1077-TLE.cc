#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;
int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
string dirChars = "durl";
int fact[10];
vector<bool> visit(370000, false);
vector<int> prevHash(370000, 0);
vector<char> prevChar(370000, ' ');
void initFact() {
  fact[0] = fact[1] = 1;
  for (int i = 2; i < 10; ++i) {
    fact[i] = i * fact[i - 1];
  }
}

class Puzzle {
  public:
    Puzzle(int x, int y, string puzzle): x(x), y(y), puzzle(puzzle) {
      calHash();
    }
    int x, y;
    string puzzle;
    bool isSolvable;
    int hash;
    void solvable() {
      int allCnt = 0;
      int n = puzzle.size(), revCnt;
      for (int i = 0; i < n; ++i) {
        int revCnt = 0;
        if (puzzle[i] == '0') continue;
        for (int j = i + 1; j < n; ++j) {
          if (puzzle[j] == '0') continue;
          if (puzzle[j] < puzzle[i]) {
            ++revCnt;
          }
        }
        allCnt += revCnt;
      }
      isSolvable = allCnt % 2 == 0;
    }
    void calHash() {
      int allCnt = 0;
      hash = 0;
      int n = puzzle.size(), revCnt;
      for (int i = 0; i < n; ++i) {
        int revCnt = 0;
        for (int j = i + 1; j < n; ++j) {
          if (puzzle[j] < puzzle[i]) {
            ++revCnt;
          }
        }
        hash += revCnt * fact[n - i - 1];
        allCnt += revCnt;
      }
      solvable();
      // cout << "hash: " << hash << "isSolvable: " << isSolvable<<endl;
    }
    bool moveTo(int i) {
      int xx = x + dirs[i][0];
      int yy = y + dirs[i][1];
      if (xx >= 0 && xx < 3 && yy >= 0 && yy < 3) {
        swap(puzzle[x * 3 + y], puzzle[xx * 3 + yy]);
        x = xx;
        y = yy;
        calHash();
      } else {
        return false;
      }
      return true;
    }
    bool moveBack(int i) {
      int xx = x - dirs[i][0];
      int yy = y - dirs[i][1];
      swap(puzzle[x * 3 + y], puzzle[xx * 3 + yy]);
      x = xx;
      y = yy;
      calHash();
      return true;
    }
    string getPath() {
      int h = hash;
      string res = "";
      while(prevHash[h] != -1) {
        res += prevChar[h];
        h = prevHash[h];
      }
      return res;
    }
};

void bfs() {
  queue<Puzzle> Q;
  string FINAL_STATE = "123456780";
  Puzzle start(2, 2, FINAL_STATE);
  Q.push(start);
  visit[start.hash] = true;
  prevHash[start.hash] = -1;
  while(!Q.empty()) {
    Puzzle &curr = Q.front();
    int curr_hash = curr.hash;
    for (int i = 0; i < 4; ++i) {
      if (curr.moveTo(i)) {
        if (!visit[curr.hash]) {
          Q.push(curr);
          prevHash[curr.hash] = curr_hash;
          prevChar[curr.hash] = dirChars[i];
          visit[curr.hash] = true;
        }
        curr.moveBack(i);
      }
    }
    Q.pop();
  }
}

int main() {
  string line;
  string puzzle = "";

  initFact();
  bfs();
  while(getline(cin, line)) {
  //while(gets(line)) {
    puzzle = "";
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == 'x') {
        puzzle += '0';
      } else if (line[i] >= '1' && line[i] <= '8') {
        puzzle += line[i];
      }
    }
    cout<<puzzle<<endl;
    Puzzle p(-1, -1, puzzle);
    if (p.isSolvable && visit[p.hash]) {
      cout << p.getPath() << endl;
    } else {
      cout << "unsolvable" << endl;
    }
  }
  return 0;
}
