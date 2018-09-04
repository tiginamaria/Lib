#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5001;
const int MAXW = MAXN * 1e5;
int n, s, f, m;
int v, u, w;
vector<int> ans;
vector< pair<int, int> > g[MAXN];
long long d[MAXN];
int p[MAXN];
bool used[MAXN];

int main() {
    cin >> n >> m >> s >> f;
    s--, f--;
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;
        g[v].push_back({--u,w});
        g[u].push_back({--v,w});
    }

    for (int i = 0; i < n; i++)
        d[i] = MAXW;

    d[s] = 0;

    for (int i = 0; i < n; i++) {
        v = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == MAXW)
            break;
        used[v] = 1;
        for (size_t j = 0; j < g[v].size(); j++) {
            u = g[v][j].first;
            w = g[v][j].second;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                p[u] = v;
            }
        }
    }
    u = f;
    if (d[f] ==  MAXW)
        cout << "no way\n";
    else {
        cout << d[f] << '\n';
        while (u != s) {
            ans.push_back(u + 1);
            u = p[u];
        }
        cout << s + 1 << ' ';
        reverse(ans.begin(), ans.end());
        for(auto v : ans)
            cout << v << ' ';
    }
}







