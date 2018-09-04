#include <bits/stdc++.h>
using namespace std;

const long long MAXW = 200000000;
const int MAXN = 25001;

int n, s, f, k, m;
int v, u, w;
deque <int> d1;
deque <int> d2;
deque <int> d3;
vector< pair<int, long long> > g[MAXN];
long long dist[MAXN];
bool used[MAXN];

inline void qclear(){
    d1.clear();
    d2.clear();
    d3.clear();
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> v >> u >> w;
        if (u != v)
            g[--v].push_back({--u, w});
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> s >> f;
        --s, --f;

        for (int i = 0; i < n; i++) {
            dist[i] = MAXW;
            used[i] = 0;
        }

        qclear();

        d1.push_front(s);
        dist[s] = 0;
        long long level = 0;

        while (d1.size() || d2.size() || d3.size()) {
            while (d1.size()) {
                v = d1.front();
                if (v == f) {
                    qclear();
                    break;
                }
                d1.pop_front();
                if (!used[v]) {
                    for (size_t i = 0; i < g[v].size(); i++) {
                        u = g[v][i].first;
                        w = g[v][i].second;
                        if (dist[u] > dist[v] + w) {
                            dist[u] = dist[v] + w;
                            if (dist[u] - level >= 1000 && dist[u] - level < 2000)
                                d2.push_back(u);
                            else
                                d3.push_back(u);
                        }
                    }
                    used[v] = 1;
                }
            }
            level += 1000;
            swap(d1, d2);
            swap(d2, d3);
        }
        if (dist[f] == MAXW)
            cout << -1 << '\n';
        else
            cout << dist[f] << '\n';
    }
}







