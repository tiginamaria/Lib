#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 200010;

ll n, m, cnt;
bool used[N];
vector <ll> g[N];

void dfs(ll v) {
    used[v] = cnt;
    for (auto to : g[v]) {
        if (!used[to])
            dfs(to);
    }
}

int main() {
    cin >> n >> m;
    ll x, y;
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 0; i < n; i++)
        if (!used[i]) {
            cnt++;
            dfs(i);
        }
    cout << cnt;
}

