#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const long long N = 1e6;

long long arr[N];

struct Node {
	int x, h = 0, sz = 0;
	long long sum = 0;
	Node *l, *r, *next;
	int ptr = 0;
	Node(Node* n) {
		x = n->x;
		h = n->h;
		sz = n->sz;
		sum = n->sum;
		l = n->l;
		r = n->r;
	}
	Node(int x, Node* l, Node* r) : x(x), sum(x), l(l), r(r), ptr(0) { }
	Node() : x(0), h(0), sz(0), sum(0), l(NULL), r(NULL), ptr(1) { }
};

struct Allocator {
	int step = sizeof(Node);
	Node* head;
	char* mem = new char [(N + 1001) * sizeof(Node)];
	
	Allocator() {
		head = reinterpret_cast<Node*>(&mem[0]);
		for (char* p = &mem[0]; p < &(mem[(N + 1000) * sizeof(Node)]); p += step)
			(reinterpret_cast<Node*>(p))->next = reinterpret_cast<Node*>(p + step);
	}
	
	Node* alloc() {
		Node* p = head;
		head = p->next;
		return p;
	}
	
	void free(Node* n) {
		Node* p = n;
		p->next = head;
		head = p;
	}
};

static long long n;

struct PArray {

	Allocator* a = new Allocator();
	Node* nullNode = new(a->alloc())Node();
	
	inline void inc_ptr(Node *v) {
		//fprintf(stderr, "inc_ptr %d\n", v->x);
		if (v == nullNode) return;
		v->ptr++;
	}
	
	inline void inc_ch_ptr(Node *v) {
		//fprintf(stderr, "inc_ch_ptr %d %d %d\n", v->x, v->l->x, v->r->x);
		if (v == nullNode) return;
		inc_ptr(v->l), inc_ptr(v->r);
	}
	
	inline void dec_ptr(Node *v) {
		//fprintf(stderr, "dec_ptr %d\n", v->x);
		if (v == nullNode) return;
		v->ptr--;
		if (!v->ptr) {
			dec_ptr(v->l), dec_ptr(v->r);
			a->free(v);
		}
	}
	
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
		//Node* v = new Node(arr[m], build(l, m - 1), build(m + 1, r));
		Node* v = new(a->alloc())Node(arr[m], build(l, m - 1), build(m + 1, r));
		inc_ch_ptr(v), update(v);
		return v;	
	}
	
	void print_total(Node* v) {
		if (v == nullNode)
			return;
		print_total(v->l);
		/*
		if (v->l == nullNode && v->r == nullNode)
			fprintf(stderr, "x = %d,  l = n,  r = n, sz = %d sum = %lld ptr = %d\n",v->x, v->sz, v->sum, v->ptr);
		else if (v->l == nullNode)
			fprintf(stderr, "x = %d,  l = n,  r = %d, sz = %d sum = %lld ptr = %d\n",v->x, v->r->x, v->sz, v->sum, v->ptr);
		else if (v->r == nullNode)
			fprintf(stderr, "x = %d,  l = %d,  r = n, sz = %d sum = %lld ptr = %d\n",v->x, v->l->x, v->sz, v->sum, v->ptr);
		else 
			fprintf(stderr, "x = %d,  l = %d,  r = %d, sz = %d sum = %lld ptr = %d\n",v->x, v->l->x, v->r->x, v->sz, v->sum, v->ptr);
		*/
		writeInt(v->x, ' ');
		print_total(v->r);
	}
	
	void print(Node* root, int l, int r) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		cut(root, al, am, ar, l, r - l);
		//fprintf(stderr, "======================================\n");
		print_total(am);
		//fprintf(stderr, "======================================\n");
		dec_ptr(al), dec_ptr(am), dec_ptr(ar);
		writeChar('\n');
	}
	
	void split(Node *n, Node* &l, Node* &r, int cnt) {
		//fprintf(stderr, "split %d %d\n", cnt, n->x);
		if (n == nullNode) {
			l = r = nullNode;
			return;
		}
		//Node* v = new Node(n);
		Node* v = new(a->alloc())Node(n);
		if (v->l->sz < cnt) {
			split(v->r, v->r, r, cnt - v->l->sz - 1);
			l = v, inc_ch_ptr(l), update(l);
		} else {
			split(v->l, l, v->l, cnt);
			r = v, inc_ch_ptr(r), update(r);
		}
	}
	
	void cut(Node* root, Node* &l, Node* &m, Node* &r, int from, int len) {
		Node *mr = nullNode;
		split(root, l, mr, from), inc_ptr(l), inc_ptr(mr);
		split(mr, m, r, len), inc_ptr(m), inc_ptr(r);
		dec_ptr(mr);
	}
	
	Node* merge(Node* l, Node* r) {
		//fprintf(stderr, "merge\n");
		if (l == nullNode) return r;
		else if (r == nullNode) return l;
		else if (l->h < r->h) {
			//Node* tmp = new Node(r->x, merge(r->l, l), r->r);
			Node* tmp = new(a->alloc())Node(r->x, merge(l, r->l), r->r);
			inc_ch_ptr(tmp), update(tmp);
			return tmp;
		} else {
			//Node* tmp = new Node(l->x, l->l, merge(l->r, r));
			Node* tmp = new(a->alloc())Node(l->x, l->l, merge(l->r, r));
			inc_ch_ptr(tmp), update(tmp);
			return tmp;
		}
	}
	
	Node* join(Node* l, Node* m, Node* r) {
		Node *lm = merge(l, m);
		inc_ptr(lm);
		Node *lmr = merge(lm, r);
		inc_ptr(lmr);
		dec_ptr(lm);
		return lmr;
	}
	
	Node* copy(Node* root, int a, int b, int l) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		Node *bl = nullNode, *bm = nullNode, *br = nullNode;
		
		cut(root, al, am, ar, a, l);
		cut(root, bl, bm, br, b, l);
		
		dec_ptr(root);
		Node *new_root = join(bl, am, br);
		
		dec_ptr(al), dec_ptr(am), dec_ptr(ar);
		dec_ptr(bl), dec_ptr(bm), dec_ptr(br);
		return new_root;
	}
	
	void get_sum(Node *root, int l, int r) {
		Node *al = nullNode, *am = nullNode, *ar = nullNode; 
		cut(root, al, am, ar, l, r - l);
		writeInt<long long>(am->sum, '\n');
		dec_ptr(al), dec_ptr(am), dec_ptr(ar);
	}
};

Node* root;
PArray p;
char task[10];
long long m, l, r, da, db;

int main() {
	
	n = readInt(); 
	arr[0] = readInt<long long>();
	da = readInt<long long>();
	db = readInt<long long>();
	m = readInt<long long>();
	for(int i = 1; i < n; i++) {
		arr[i] = ((arr[i - 1] * (long long )da) + db) % m;
		//arr[i] = arr[i - 1] + 1; 
	}
	root = p.build(0, n - 1);
	p.inc_ptr(root);
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





