#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;

struct Edge {
	int v;
	int w;
};

const int MAXN = 5e4;
int d[MAXN];
int p[MAXN];
int f[16][MAXN];
vector<Edge> g[MAXN];
int n, m;

void getans(int v, int dp, int pr = -1, int emin = INT_MAX) {
	f[dp][v] = emin;
	for (Edge x : g[v])
		if (d[x.v] == -1 && x.v != pr)
			getans (x.v, dp, v, min(emin, x.w));
}

int getc(int v, int u) {
	while (d[v] < d[u]) u = p[u];
	while (d[u] < d[v]) v = p[v];
	while (v != u) v = p[v], u = p[u];
	return v;
}

int get(int v, int u) {
	int c = getc(v, u);
	return min(f[d[c]][v], f[d[c]][u]);
}

int dfs( int v, int s, int &c, int pr = -1) {
	int cnt = 1;
	for (Edge x : g[v])
		if (d[x.v] == -1 && pr != x.v)
			cnt += dfs(x.v, s, c, v);
	if (c == -1 && (s <= 2 * cnt || pr == -1))
		c = v;
	return cnt;
}

void build( int v, int s, int dp, int pr) {
	int c = -1;
	dfs(v, s, c);
	getans(c, dp);
	d[c] = dp;
	p[c] = pr;
	for (Edge x : g[c])
		if (d[x.v] == -1)
			build(x.v, s / 2, dp + 1, c);			
}

int main() {
	n = readInt();
	int x, y;
	for (int i = 0; i < n; i++) {
		d[i] = -1;
		p[i] = -1;
	}
	for (int i = 1; i < n; i++) {
		x = readInt() -1;
		y = readInt();
		g[x].push_back({i, y});
		g[i].push_back({x, y});
	}
	build(0, n, 0, -1);
   	m = readInt();
	for (int i = 0; i < m; i++) {
		x = readInt() - 1;
		y = readInt() - 1;
		writeInt(get(x, y), '\n');
	}
}   





