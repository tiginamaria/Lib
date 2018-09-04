#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000;
const long long MAXW = 1e15;
const long long MAXM = MAXN * 2 * MAXW;

struct Edge {
    int start, end;
    long long weight;
    Edge(int s, int e, long long w) : start(s), end(e), weight(w) {}
};

vector < Edge > g;
long long d[MAXN];
int n, m, s, u, v;
long long w;


int main() {
    cin >> n >> m >> s;
    s--;
    for (int i = 0; i < m; i++) {
        cin >> v, v--;
        cin >> u, u--;
        cin >> w;
        g.push_back(Edge(v, u, w));
    }

    for (int i = 0; i < n; i++)
        d[i] = MAXM;

    d[s] = 0;

    for (int k = 0; k < 2 * n; k++)
        for (auto e : g)
            if (d[e.start] < MAXM && (d[e.end] > d[e.start] + e.weight)) {
                if (k < n)
                    d[e.end] = max(-MAXM,(long long)d[e.start] + e.weight);
                else
                    d[e.end] = -MAXM;
            }

    for (int k = 0; k < n; k++)
        if (d[k] == -MAXM)
            cout << "no path\n";
        else if (d[k] == MAXM)
            cout << "no shortest path\n";
        else
            cout << d[k] << '\n';
}




