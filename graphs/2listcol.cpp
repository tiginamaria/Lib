#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2 * 1001;

int n, m;

struct Vertex {
    char c0;
    char c1;
};

vector <int> sat[MAXN], isat[MAXN], top;
Vertex c[MAXN];
int comp[MAXN];
bool used[MAXN];

void dfs1(int v) {
    used[v] = 1;
    for (auto u : sat[v])
        if (!used[u])
            dfs1(u);
    top.push_back(v);
}

void dfs2(int v, int cnt) {
    comp[v] = cnt;
    for (auto u : isat[v])
        if (!comp[u])
            dfs2 (u, cnt);
}

int main()
{
    cin >> n >> m;
    char colour;
    for (int i = 0; i < n; i++) {
        cin >> colour;
        if (colour == 'R')
            c[i] = {'G', 'B'};
        if (colour == 'G')
            c[i] = {'R', 'B'};
        if (colour == 'B')
            c[i] = {'R', 'G'};
    }

    int v, u;

    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        --v, --u;
        if (c[u].c0 == c[v].c0) {
            sat[u + n].push_back(v);
            sat[v + n].push_back(u);
            isat[v].push_back(u + n);
            isat[u].push_back(v + n);
        }
        if (c[u].c0 == c[v].c1) {
            sat[u + n].push_back(v + n);
            sat[v].push_back(u);
            isat[v + n].push_back(u + n);
            isat[u].push_back(v);
        }
        if (c[u].c1 == c[v].c0) {
            sat[u].push_back(v);
            sat[v + n].push_back(u + n);
            isat[v].push_back(u);
            isat[u + n].push_back(v + n);
        }
        if (c[u].c1 == c[v].c1) {
            sat[u].push_back(v + n);
            sat[v].push_back(u + n);
            isat[v + n].push_back(u);
            isat[u + n].push_back(v);
        }
    }

    n *= 2;

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    reverse(top.begin(), top.end());

    int k = 0;
    for (int i = 0; i < n; i++) {
        v = top[i];
        if (!comp[v]) {
            k++;
            dfs2(v, k);
        }
    }

    bool imp = 0;
    n /= 2;

    for (int i = 0; i < n; i++)
        if (comp[i] > comp[i + n])
            swap (c[i].c0, c[i].c1);
        else if(comp[i] == comp[i + n])
            imp = 1;

    if (imp)
        cout << "Impossible";
    else
        for (int i = 0; i < n; i++)
            cout << c[i].c0;
}

