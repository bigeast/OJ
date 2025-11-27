#include <bits/stdc++.h>
using namespace std;

// ----------------------------------------------------
// Kuhn 匈牙利 DFS 匹配模板
// ----------------------------------------------------
vector<int> adj[20005];   // 二分图：左部 -> 右部
int matchR[20005];        // 右部的匹配点
bool vis[20005];          // DFS 访问标记

bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = true;

        if (matchR[v] == -1 || dfs(matchR[v])) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

// ----------------------------------------------------
// 主程序：读取数据、构造图、染色、匹配
// ----------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (true) {
        if (!(cin >> n)) break;       // EOF
        if (n <= 0) continue;

        // 清空
        vector<vector<int>> G(n);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }

        // ------------------------------------------------
        // 输入格式：
        // id: (k) a b c ...
        // ------------------------------------------------
        for (int i = 0; i < n; i++) {
            int id;
            char ch;
            cin >> id >> ch;  // id:
            cin >> ch;        // '('
            int k;
            cin >> k >> ch;   // k ')'
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                G[id].push_back(x);
                G[x].push_back(id);
            }
        }

        // ------------------------------------------------
        // Step 1: 二分染色
        // ------------------------------------------------
        vector<int> color(n, -1);

        function<void(int)> dfs_color = [&](int u) {
            for (int v : G[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    dfs_color(v);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                color[i] = 0;
                dfs_color(i);
            }
        }

        // ------------------------------------------------
        // Step 2: 构造二分图（只加 color=0 -> color=1 的边）
        // ------------------------------------------------
        for (int u = 0; u < n; u++) {
            if (color[u] == 0) {
                for (int v : G[u]) {
                    // v 必然为 1
                    adj[u].push_back(v);
                }
            }
        }

        // ------------------------------------------------
        // Step 3: 匈牙利最大匹配
        // ------------------------------------------------
        memset(matchR, -1, sizeof(matchR));

        int maxMatch = 0;
        for (int u = 0; u < n; u++) {
            if (color[u] != 0) continue;  // 只从左部启动 DFS
            memset(vis, 0, sizeof(vis));
            if (dfs(u)) maxMatch++;
        }

        // ------------------------------------------------
        // Step 4: 输出最大独立集大小 = n - 最大匹配
        // ------------------------------------------------
        cout << n - maxMatch << "\n";
    }

    return 0;
}
