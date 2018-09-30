#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int N = 1e6;

int a[N];

struct Node {
	Node *lsub, *rsub;
	int x, l, r;
	Node(int x, int l, int r) : x(x), l(l), r(r) { }
	Node(Node* ls, Node* rs, int l, int r) : lsub(ls), rsub(rs), l(l), r(r) { }
};

struct PArray {
	void print_total(Node* n) {
		if (n->l == n->r) {
			fprintf(stderr, "x = %d l = %d\n", n->x, n->l);
			return;
		}
		print_total(n->lsub);
		fprintf(stderr, "    l = %d, r = %d\n", n->l, n->r);
		print_total(n->rsub);
	}
	
	Node* build(int l, int r) {
	//fprintf(stderr, "build %d %d", l, r);
		if (l == r) {
			return new Node(a[l], l, r);
		}	
		int m = (l + r) >> 1;
		return new Node(build(l, m), build(m + 1, r), l, r);	
	}
	
	int get(Node* n, int i) {
	//fprintf(stderr, "get %d\n", i);
		if (n->l == n->r && n->l == i)
			return n->x;
		int m = (n->l + n->r) >> 1;
		return (i <= m) ? get(n->lsub, i) : get(n->rsub, i);
	}
	
	Node* set(Node* n, int i, int x) {
	//fprintf(stderr, "set %d %d %d %d\n",n->l, n->r, i, x);
		if (i < n->l || i > n->r)
			return n;
		if (n->l == n->r)
			return new Node(x, n->l, n->r);
		return new Node(set(n->lsub, i, x), set(n->rsub, i, x), n->l, n->r);
	}
};

Node* root[N];
PArray p;
string task;
int cnt = 1, v, i, x, n, m;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	root[cnt] = p.build(1, n);
	//fprintf(stderr, "===============%d================\n", cnt);
	//p.print_total(root[cnt]);
	//fprintf(stderr, "===============================\n");
	cin >> m;
	
	for (int j = 0; j < m; j++) {
		cin >> task;
		if (task == "create") {
			cin >> v >> i >> x;
			//fprintf(stderr, "create %d %d %d \n", v, i, x);
			cnt++;
			root[cnt] = p.set(root[v], i, x);
			//fprintf(stderr, "===============%d================\n", cnt);
			//p.print_total(root[cnt]);
			//fprintf(stderr, "===============================\n");
		}
		if (task == "get") {
			cin >> v >> i;
			//fprintf(stderr, "get %d %d \n", v, i);
			cout << p.get(root[v], i) << endl;
			//fprintf(stderr, "===============%d================\n", v);
			//p.print_total(root[v]);
			//fprintf(stderr, "===============================\n");
		}
	}
}   





