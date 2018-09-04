#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;

const int MAXN = INT_MAX;
int n, s, m;
int v, u;
queue<int> q;
vector<int> g[100001];
int d[100001];

int main() {
    n = readInt();
    s = readInt();
    m = readInt();
    s--;
    for (int i = 0; i < m; i++) {
        v = readInt();
        u = readInt();
        u--, v--;
        g[u].push_back(v);
    }

    for (int i = 0; i < n; i++)
        d[i] = MAXN;

    q.push(s);
    d[s] = 0;

    while (q.size()) {
        v = q.front();
        q.pop();
        for (auto to : g[v]) {
            if (d[to] == MAXN) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (d[i] == MAXN)
            writeInt(-1,' ');
        else
            writeInt(d[i],' ');
}







