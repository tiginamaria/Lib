#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const long long MAXM = 2e7;
const double EPS = 1e-9;

struct Edge {
    int start, end, weight, num;
    Edge(int s, int e, int w, int n) : start(s), end(e), weight(w), num(n) {}
};

vector < Edge > g;
vector < int > ans;
double d[MAXN];
int p[MAXN];
bool used[MAXN];
int w, n, m, v, u, minw = 1000, maxw = -1000, e, x;
double l, r, dx, minc;

int ford(double dx) {
    int x = -1;
    for (int i = 0; i < n; i++) {
        p[i] = -1;
        d[i] = MAXM;
    }

    d[0] = 0;
    for (int k = 0; k < n; k++) {
        x = -1;
        for (auto e : g) {
            if (d[e.end] > d[e.start] + e.weight - dx + EPS) {
                if (d[e.start] + e.weight - dx + EPS < -MAXM)
                    d[e.end] = -MAXM;
                else
                    d[e.end] = d[e.start] + e.weight - dx;
                p[e.end] = e.num;
                x = e.num;
                if (k == n - 1)
                    return x;
            }
        }
    }
    return x;
}

int main() {

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> v; v--;
        cin >> u; u--;
        cin >> w;
        minw = min(minw, w);
        maxw = max(maxw, w);
        g.push_back(Edge(v, u, w, i));
    }

    l = minw;
    r = minc = maxw;
    while(l + EPS < r) {
        dx = (l + r) / 2;
        if (ford(dx) != -1)
            r = dx;
        else
            l = dx;
    }

    x = ford(r);

    while (!used[g[x].start]) {
        used[g[x].start] = 1;
        x = p[g[x].start];
    }

    minc = 0;
    e = x;

    while (e != x || ans.empty()) {
        ans.push_back(e);
        minc += g[e].weight;
        e = p[g[e].start];
    }

    cout.setf(std::ios::fixed);
    cout.precision(9);
    cout << fixed << minc/ans.size() << '\n';
    cout << ans.size() << '\n';

    while (ans.size()) {
        cout << ans.back() + 1 << ' ';
        ans.pop_back();
    }
}








