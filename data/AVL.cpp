#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int N = 1e5;
const int INF = 1e9;
int n, l, r, x;

struct Node {
	Node *l, *r, *p;
	int key, h;
	long long sz;
	bool del;
	Node();
	Node(int k, Node* pr);
};

unordered_map<int, Node*> m;

Node::Node() { }
Node* nullNode = new Node();

Node::Node(int k, Node* pr) {
	key = k;
	p = pr;
	sz = 1;
	l = r = nullNode;
	h = 1;
	del = 0;
}

Node* root;

void update(Node *v) {
	//fprintf(stderr, "update %d\n", v->key);
	if (v != nullNode) {
		v->sz = (v->l)->sz + (v->r)->sz + ((v->del) ? 0 : 1);
		v->h = max((v->l)->h, (v->r)->h) + 1;
	}
}

void recalc(Node *v) {
	if (v != nullNode) {
		update(v);
		recalc(v->p);
	}
} 

Node* rotate_left(Node *v) {
	//fprintf(stderr, "rotate_l %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->l;
	tmp->p = v->p;
	v->l = tmp->r;
	if (tmp->r != nullNode) (tmp->r)->p = v;
	update(v);
	tmp->r = v;
	v->p = tmp; 
	update(tmp);
	return tmp;
}

Node* rotate_right(Node *v) {
	//fprintf(stderr, "rotate_r %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->r;
	tmp->p = v->p;
	v->r = tmp->l;
	if (tmp->l != nullNode) (tmp->l)->p = v;
	update(v);
	tmp->l = v, v->p = tmp;
	update(tmp);
	return tmp;
}

Node* rotate_left_right(Node *v) {
	//fprintf(stderr, "rotate_lr %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->l;
	v->l = rotate_right(tmp);
	return rotate_left(v);
}

Node* rotate_right_left(Node *v) {
	//fprintf(stderr, "rotate_rl %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->r;
	v->r = rotate_left(tmp);
	return rotate_right(v);
}

int diff(Node *v) {
	//fprintf(stderr, "diff %d kids = %d \n", v->key, (v->l)->h - (v->r)->h);
	return (v->l)->h - (v->r)->h;
}
/*
void printAVL(Node* v) {
	if (v == nullNode) return;
	printAVL(v->l);
	printf("key = %d h = %d sz = %lld del = %d p = %d ", v->key, v->h, v->sz, v->del, (v->p)->key);
	if (v->l != nullNode)
		printf("l_child - %d ", (v->l)->key);
	else
		printf("l_child - null ");
	if (v->r != nullNode)
		printf("r_child - %d ", (v->r)->key);
	else 
		printf("r_child - null ");
	printf("\n");
	printAVL(v->r);
}
*/
Node* rotate(Node *v) {
	if (v == nullNode) return nullNode;
	//fprintf(stderr, "rotate %d\n", v->key);
	update(v);
	if(diff(v) > 1) {
		if(diff(v->l) > 0) 
			v = rotate_left(v);
		else 
			v = rotate_left_right(v);
	} else if(diff(v) < -1) {
		if(diff(v->r) > 0) 
			v = rotate_right_left(v);
		else 
			v = rotate_right(v);
	}
	update(v);
	return v;
}

Node* add(Node* v, Node* p, int k) {
	if (v == nullNode) {
		//fprintf(stderr, "add new ");
		//fprintf(stderr, "%d\n", k);
		m[k] = new Node(k, p);
		return m[k];
	} else {
		if (k < v->key) {
			//fprintf(stderr, "skip_l %d ", v->key);
			v->l = add(v->l, v, k);
		} else {  
			//fprintf(stderr, "skip_r %d ", v->key);
			v->r = add(v->r, v, k);
		}
		update(v);
		v = rotate(v);
	}
	return v;
}

bool find(Node* v, int k) {
	if (v == nullNode) return 0;
	if (v->key == k) return 1;
	if (v->key > k) return find(v->l, k);
	if (v->key < k) return find(v->r, k);
	return 0;
}

void del(Node *v, int k) {
	if (v == nullNode) return;
	if (v->key == k) {
		v->del = 1;
		recalc(v);
	}
	if (v->key > k)
		del(v->l, k);
	if (v->key < k)
		del(v->r, k);
}

int kmax(Node *v, int k) {
	if(v->r->sz == k - 1 && !v->del) {
		//fprintf(stderr,  "k %d %d\n", 1, v->key);
		return v->key;
	} else if(v->r->sz > k - 1) {
		//fprintf(stderr,  "k->r %d %d\n", 2, v->key);
		return kmax(v->r, k);
	} else {
		//fprintf(stderr,  "k->l %d %lld %lld\n", 3, k - v->r->sz - ((v->del) ? 0 : 1),  v->r->sz);
		return kmax(v->l, k - v->r->sz - ((v->del) ? 0 : 1));
	}
}

int main() {
	//n = readInt();
	cin >> n;
	nullNode->r = nullNode;
	nullNode->l = nullNode;
	nullNode->p = nullNode;
	nullNode->h = 0;
	nullNode->sz = 0;
	nullNode->key = 0;
	
	root = nullNode;
	int task;
	for (int i = 0; i < n; i++) {
		task = readInt();
		//cin >> task;
		//fprintf(stderr, "%d\n", task);
		if (task == 1) {
			x = readInt();
			//cin >> x;
			if (!m.count(x)) {
				//fprintf(stderr, "___________add %lld____________\n", x);
				root = add(root, root->p, x);
			} else {
				(m[x])->del = 0;
				recalc(m[x]); 
			}
		}
		if (task == -1) {
			x = readInt();
			//cin >> x;
			del(root, x);
		} 
		if (task == 0) {
			x = readInt();
			//cin >> x;
			//fprintf(stderr, "___________kmax %d____________\n", x);
			writeInt(kmax(root, x), '\n');
			//cout << kmax(root, x) << '\n';
		}
		//printf("==========total============\n");
		//printAVL(root);
		//printf("===========================\n\n");
	}
}   

