#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const long long N = 1e6;

long long a[N];

struct Node {
	int x, h = 0, sz = 0;
	long long sum = 0;
	Node *l, *r;
	Node();
	Node(Node* n) {
		x = n->x;
		h = n->h;
		sz = n->sz;
		sum = n->sum;
		l = n->l;
		r = n->r;
	}
	Node(int x, Node* l, Node* r) : x(x), sum(x), l(l), r(r) { }
};

Node::Node() { }
Node* nullNode = new Node();

struct PArray {
	void update(Node *v) {
		//fprintf(stderr, "update %d\n", v->x);
		if (v != nullNode) {
			v->sz = (v->l)->sz + (v->r)->sz + 1;
			v->sum = (v->l)->sum + (v->r)->sum + v->x;
			v->h = max((v->l)->h, (v->r)->h) + 1;
		}
	}

	Node* build(int l, int r) {
		//fprintf(stderr, "build %d %d\n", l, r);
		if (l > r)
			return nullNode;
		int m = (l + r) >> 1;
		Node* v = new Node(a[m], build(l, m - 1), build(m + 1, r));
		update(v);
		return v;	
	}
	
	void print_total(Node* v) {
		if (v == nullNode)
			return;
		print_total(v->l);
		//fprintf(stderr, "x = %d,  l = %d,  r = %d, sz = %d sum = %lld\n",v->x, v->l->x, v->r->x, v->sz, v->sum);
		writeInt(v->x, ' ');
		print_total(v->r);
	}
	
	void print(Node* root, int l, int r) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		split(root, al, am, l);
		split(am, am, ar, r - l);
		print_total(am);
		writeChar('\n');
	}
	
	void split(Node *n, Node* &l, Node* &r, int cnt) {
	//fprintf(stderr, "split %d %d %d\n", cnt, l->x, r->x);
		if (n == nullNode) {
			l = r = nullNode;
			return;
		}
		Node* v = new Node(n);
		if (v->l->sz < cnt) {
			split(v->r, v->r, r, cnt - v->l->sz - 1);
			l = v, update(l);
		} else {
			split(v->l, l, v->l, cnt);
			r = v, update(r);
		}
	}

	Node* merge(Node* l, Node* r) {
	//fprintf(stderr, "merge\n");
		if (l == nullNode) return r;
		else if (r == nullNode) return l;
		else if (l->h > r->h) {
			l->r = new Node(merge(l->r, r));
			update(l);
			return l;
		} else {
			r->l = new Node(merge(l, r->l));
			update(r);
			return r;
		}
	}

	Node* copy(Node* root, int a, int b, int l) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		Node *bl = nullNode, *bm = nullNode, *br = nullNode; 
		split(root, al, am, a);
		split(am, am, ar, l);
		split(root, bl, bm, b);
		split(bm, bm, br, l);
		return merge(merge(bl, am), br);
	}
	
	void get_sum(Node *root, int l, int r) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		split(root, al, am, l);
		split(am, am, ar, r - l);
		writeInt<long long>(am->sum, '\n');
	}
};

Node* root;
PArray p;
char task[10];
long long n, m, l, r, da, db;

int main() {
	nullNode->r = nullNode;
	nullNode->l = nullNode;
	nullNode->h = 0;
	nullNode->sz = 0;
	nullNode->sum = 0;
	nullNode->x = 0;
	
	n = readInt();
	a[0] = readInt<long long>();
	da = readInt<long long>();
	db = readInt<long long>();
	m = readInt<long long>();
	for(int i = 1; i < n; i++) {
		a[i] = ((a[i - 1] * da) % m + db) % m;
	}
	root = p.build(0, n - 1);
	m = readInt();
	for (int j = 0; j < m; j++) {
		readWord(task);
		if (task[0] == 'o') {
			//writeWord(task);
			l = readInt() - 1;
			r = readInt();
			p.print(root, l, r);
		}
		if (task[0] == 's') {
			//writeWord(task);
			l = readInt() - 1;
			r = readInt();
			p.get_sum(root, l, r);
		}
		if (task[0] == 'c') {
			//writeWord(task);
			da = readInt() - 1;
			db = readInt() - 1;
			l = readInt();
			root = p.copy(root, da, db, l);
		}
	}
}   





