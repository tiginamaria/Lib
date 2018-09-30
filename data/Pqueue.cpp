#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int N = 2e5;

int a[N];
int l[N];
int r[N];

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
int task;
int cnt, v, i, x, n, m;


int main() {
	cin >> n;
	root[cnt] = p.build(1, n);
	//fprintf(stderr, "===============%d================\n", cnt);
	//p.print_total(root[cnt]);
	//fprintf(stderr, "===============================\n");
	l[0] = 1, r[0] = 0;
	for (int j = 0; j < n; j++) {
		task = readInt();
		if (task == 1) {
			v = readInt();
			x = readInt();
			//fprintf(stderr, "create %d %d %d \n", v, i, x);
			cnt++;
			l[cnt] = l[v];
			r[cnt] = r[v] + 1;
			root[cnt] = p.set(root[v], r[cnt], x);
			//fprintf(stderr, "1===============%d================\n", cnt);
			//p.print_total(root[cnt]);
			//fprintf(stderr, "===============================\n");
		}
		if (task == -1) {
			v = readInt();
			//fprintf(stderr, "get %d %d \n", v, i);
			writeInt(p.get(root[v], l[v]), '\n');
			cnt++;
			root[cnt] = root[v];
			l[cnt] = l[v] + 1;
			r[cnt] = r[v];
			//fprintf(stderr, "-1===============%d================\n", v);
			//p.print_total(root[v]);
			//fprintf(stderr, "===============================\n");
		}
	}
}   





