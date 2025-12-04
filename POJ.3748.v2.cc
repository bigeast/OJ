#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int char2int(char c) {
  int res = 0;
  if (c >= '0' && c <= '9') res += c - '0';
  else if (c >= 'a' && c <= 'f') res += c - 'a' + 10;
  else if (c >= 'A' && c <= 'F') res += c - 'A' + 10;
  return res;
}

int main() {
  char s[100];
  int n = 0, x = 0, y = 0;
  scanf("%s", s);

  char *p = s;
  int neg = 1;
  // 不处理前缀也能过
  /*
  if (*p == '-') {
    neg = -1;
    p++;
  }
  if (*p == '0' && *(p + 1) == 'x') {
    p += 2;
  }
  */
  while (*p!=',') {
    n *= 16;
    n += char2int(*p++);
  }
  // 应该先++跳过逗号
  while (*(++p)!=',') {
    x *= 10;
    x += char2int(*p);
  }
  // 判断结束
  while (*(++p) != ',' && *p != 0) {
    y *= 10;
    y += char2int(*p);
  }
  n *= neg;
  n &= ~(1<<x)
  n |= (1<<y);
  n |= (1<<(y-1));
  n &= ~(1<<(y-2));
  printf("%x\n", n);
  return 0;
}
