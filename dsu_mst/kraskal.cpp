#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int MAXM = 1e5;
const int MAXN = 20000;
const int MAXW = 1e5;
struct Edge {
    int from;
    int to;
    int w;
};

Edge g[MAXM];
int p[MAXN];
int n, m, v, u, w;
long long weight;

void init() {
    for (int i = 0; i < n; i++)
        p[i] = i;
}

int get(int i) {
    return (p[i] == i) ? i : (p[i] = get(p[i]));
}

void join(Edge e) {
    int s = get(e.from);
    int t = get(e.to);
    if (s != t) {
        p[s] = t;
        weight += e.w;
    }
}

bool comp (Edge e1, Edge e2) {
    return e1.w < e2.w;
}

int main() {
    n = readInt();
    m = readInt();
    for (int i = 0; i < m; i++) {
        v = readInt() - 1;
        u = readInt() - 1;
        w = readInt();
        g[i] = {v, u, w};
    }

    sort(g, g + m, comp);

    init();

    for (int i = 0; i < m; i++)
        join(g[i]);
    writeInt(weight,'\n');
}

