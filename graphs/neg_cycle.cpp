#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
const long long MAXM = 1e6;
struct Edge {
    int start, end, weight;
    Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};

vector < Edge > g;
vector < int > ans;
long long d[MAXN];
int p[MAXN];
int w, n, m, x;

int main() {
    x = -1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w;
            if (j == i && w < 0)
                x = i;
            if (w != 100000)
                g.push_back(Edge(i, j, w));
        }
    }
    if (x != -1) {
        cout << "YES\n";
        cout << 1, '\n' << x + 1;
    } else {
        m = g.size();
        for (int i = 0; i < n; i++) {
            p[i] = -1;
            d[i] = MAXM;
        }

        d[rand() % n] = 0;

        for (int k = 0; k < n; k++) {
            x = -1;
            for (auto e : g) {
                if (d[e.end] > d[e.start] + e.weight) {
                    d[e.end] = max (-MAXM, d[e.start] + e.weight);
                    p[e.end] = e.start;
                    x = e.end;
                }
            }
        }
        if (x == -1)
            cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                x = p[x];
            }
            int v = x;
            while (v != x || ans.empty()) {
                ans.push_back(v);
                v = p[v];
            }
            cout << ans.size()  << '\n';
            reverse(ans.begin(), ans.end());
            for (auto v : ans)
                cout << v + 1 << ' ';
        }
    }
}

