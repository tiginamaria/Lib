#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
int n, m, k, cnt;
const int MAXN = 20001;
struct Edge {
    int id;
    int to;
    int from;
};
vector <Edge> g[MAXN], ans;
bool e[MAXN * MAXN];
int deg[MAXN];

void dfs(int v) {
    while (g[v].size()) {
        Edge edg = g[v].back();
        g[v].pop_back();
        if (e[edg.id]) {
            e[edg.id] = 0;
            if (v == edg.to)
                swap(edg.to, edg.from);
            dfs(edg.to);
            ans.push_back(edg);
        }
    }
}

int main()
{
    cin >> n >> m;
    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        --x, --y;

        deg[x]++, deg[y]++;
        g[x].push_back({k, x, y});
        g[y].push_back({k, x, y});
        e[k] = 1;
        k++;
    }

    int odd = -1;
    int first = -1;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) {
            if (odd == -1)
                odd = i;
            else {
                first = odd;

                g[i].push_back({k, i, odd});
                g[odd].push_back({k, i, odd});

                e[k] = 1;
                odd = -1;
                k++;
            }
        }
    }
    if (first == -1) {
        first = 0;
        cnt = 1;
    } else
        cnt = k - m;

    dfs(first);
    cout << cnt << '\n';
    if (ans.back().id >= m)
        ans.pop_back();
    while(ans.size()) {
        cout << ans.back().from + 1 << ' ';
        while(ans.size() && ans.back().id < m) {
            cout << ans.back().to + 1 << ' ';
            ans.pop_back();
        }
        if (ans.size())
            ans.pop_back();
        cout << '\n';
    }
}


