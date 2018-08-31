#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll N = 20010;
ll t = 0, n, m;
bool used[N];
vector <pair <ll, ll> > g[N];
ll timein[N], up[N];
vector <ll> bridges;

void dfs(int v, int p) {
    used[v] = 1;
    t++;
    timein[v] = t;
    up[v] = t;
    for (auto e : g[v]) {
        ll to = e.first;
        ll num = e.second;
        if (p == to) continue;
        if (used[to])
            up[v] = min(up[v], timein[to]);
        else {
            dfs(to, v);
            up[v] = min(up[v], up[to]);
            if (timein[v] < up[to])
                bridges.push_back(num);
        }
    }
}
int main() {
    ll n, m;
    cin >> n >> m;
    ll v, u;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        g[v].push_back({u, i});
        g[u].push_back({v, i});
    }
    for(int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, -1);

    for (auto e : bridges)
        cout << e;

}

