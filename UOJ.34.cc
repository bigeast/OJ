#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>
using namespace std;

// 多项式乘法模板题
// https://uoj.ac/problem/34
// 开始还没太理解怎么这么简单的问题也需要模板，是有什么语法糖吗，然后第一个用例就超时，搜了一下才知道是用 FFT。
// 想当年数字信号处理也是学得挺好的，只是 FFT 这块一直没怎么搞明白。
// 模板题的意义还是很大的，能称之为模板，终归是足够经典。

const int N = 100001;
const double PI = acos(-1.0);

// 定义复数类型
typedef complex<double> cd;

// 快速傅里叶变换 (FFT)
// a: 输入/输出的系数或点值数组
// invert: true 表示进行逆 FFT (IFFT)，false 表示进行正向 FFT
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    
    // 位反转置换 (Bit-reversal permutation)
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Butterfly 操作，逐级合并
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // 如果是逆 FFT (IFFT)，需要除以 N
    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

// 多项式乘法函数
// a, b: 输入多项式的系数数组
// 返回值: 乘积多项式的系数数组
vector<long long> multiply(const vector<int>& a, const vector<int>& b) {
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    int n = 1;
    
    // 找到大于等于 (a.size() + b.size()) 的最小 2 的幂作为 FFT 长度 N
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // 正向 FFT 转换为点值表示
    fft(fa, false);
    fft(fb, false);

    // 点值相乘
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    // 逆向 IFFT 转换回系数表示
    fft(fa, true);

    // 将复数结果转换为整数系数
    vector<long long> result(a.size() + b.size() - 1);
    for (int i = 0; i < result.size(); i++) {
        // 使用 round 避免浮点误差导致的 4.99999999 或 5.00000001
        result[i] = round(fa[i].real());
    }
    
    return result;
}

int main() {
  int n, m, x;
  cin >> n >> m;
  vector<int> a, b;
  for (int i = 0; i <= n; ++i) {
    cin >> x;
    a.push_back(x);
  }
  for (int i = 0; i <= m; ++i) {
    cin >> x;
    b.push_back(x);
  }
  vector<long long> c = multiply(a, b);

  for (int i = 0; i < c.size() - 1; ++i) {
    cout << c[i] << " ";
  }
  cout << c[c.size() - 1] << endl;
  return 0;
}
