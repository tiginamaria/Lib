#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int N = 1e5;
const int INF = 1e9;
int n, m, l, r, x, y, ans;

struct Node {
	Node *l, *r, *p;
	int key, min_key, h;
	long long sz;
	bool del;
	Node();
	Node(int k, Node* pr);
};

Node::Node() { }
Node* nullNode = new Node();

Node::Node(int k, Node* pr) {
	key = k;
	min_key = k;
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
		v->min_key = min(min((v->l)->min_key, (v->r)->min_key), v->key);
		v->sz = (v->l)->sz + (v->r)->sz + 1;
		v->h = max((v->l)->h, (v->r)->h) + 1;
	}
}

void recalc(Node *v) {
	//fprintf(stderr, "recalc %d\n", v->key);
	if (v != nullNode) {
		update(v);
		recalc(v->p);
	}
} 

Node* rotate_left(Node *v) {
	//fprintf(stderr, "rotate_l %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->l;
	v->l = tmp->r;
	update(v);
	tmp->r = v;
	update(tmp);
	return tmp;
}

Node* rotate_right(Node *v) {
	//fprintf(stderr, "rotate_r %d\n", v->key);
	if (v == nullNode) return nullNode;
	Node* tmp = v->r;
	v->r = tmp->l;
	update(v);
	tmp->l = v;
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
void print_total(Node* v) {
	if (v == nullNode) return;
	print_total(v->l);
	fprintf(stderr, "key = %d h = %d sz = %lld del = %d p = %d mink = %d ", v->key, v->h, v->sz, v->del, (v->p)->key, v->min_key);
	if (v->l != nullNode)
		fprintf(stderr, "l_child - %d ", (v->l)->key);
	else
		fprintf(stderr, "l_child - null ");
	if (v->r != nullNode)
		fprintf(stderr, "r_child - %d ", (v->r)->key);
	else 
		fprintf(stderr, "r_child - null ");
	fprintf(stderr, "\n");
	print_total(v->r);
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

Node* add(Node* v, Node* p, int k, int data) {
	if (v == nullNode) {
		//fprintf(stderr, "add new ");
		//fprintf(stderr, "%d\n", k);
		return new Node(data, p);
	} else if (v->l->sz < k) {
		//fprintf(stderr, "skip_l %d ", v->key);
		v->r = add(v->r, v, k - v->l->sz - ((v->del) ? 0 : 1), data);
	} else {  			
		//fprintf(stderr, "skip_r %d ", v->key);
		v->l = add(v->l, v, k, data);
	}
	update(v);
	v = rotate(v);
	//fprintf(stderr, "end %d", v->key);
	return v;
}

int get_min(Node *v, int l, int r) {
	if (v == nullNode) {
		//fprintf(stderr, "null \n");
		return INF;
	}
	if (r < l) {
		//fprintf(stderr, "%d r < l \n", v->key);
		return INF;
	}
	if (r < 0) {
		//fprintf(stderr, "%d r < 0\n", v->key);
		return INF;
	}
	if (v->sz < l) {
		//fprintf(stderr, "%d v->sz < l \n", v->key);
		return INF;
	}
	if (l <= 0 && v->sz <= r) {
		//fprintf(stderr, "%d l = 0 && v->sz <= r\n", v->key);
		return v->min_key;
	}
	if (v->l->sz + 1 >= l && v->l->sz + 1 <= r) {
		//fprintf(stderr, "%d 1 \n", v->key);
		return min(min(get_min(v->l, l, r), get_min(v->r, 0, r - v->l->sz - 1)), v->key);
	}	
	//fprintf(stderr, "%d 2 \n", v->key);
	return min(get_min(v->l, l, r), get_min(v->r, l - v->l->sz - 1, r - v->l->sz - 1));
}

int main() {
	n = readInt();
	nullNode->r = nullNode;
	nullNode->l = nullNode;
	nullNode->p = nullNode;
	nullNode->h = 0;
	nullNode->sz = 0;
	nullNode->key = 0;
	nullNode->min_key = INF;
	
	root = nullNode;
	
	char task;
	//string task;
	for (int i = 0; i < n; i++) {
		task = readChar();
		//cin >> task;
		if (task == '+') {
			x = readInt();
			y = readInt();
			//fprintf(stderr, "___________add %d %d____________\n", x, y);
			root = add(root, root->p, x, y);
		}
		if (task == '?') {
			//fprintf(stderr, "___________del %d____________\n", x);
			l = readInt();
			r = readInt();
			writeInt(get_min(root, l, r), '\n');
		} 
		//fprintf(stderr, "==========total============\n");
		//print_total(root);
		//fprintf(stderr, "===========================\n\n");
	}
}   

