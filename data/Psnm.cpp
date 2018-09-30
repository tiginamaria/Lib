#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int MAXN = 1e6;

struct Node {
	int a, b, id = 0;
	char task;
	vector<Node*> next;
	Node() { }
};

struct Change {
	int a, b, p;
	bool r = 0;
	Change() { }
};


int r[MAXN];
int p[MAXN];
int n, m, k;
int ans[MAXN];
vector<Change*> st;
Node* v[MAXN];

struct PDSU {

	Node* init(int n) {
		for(int i = 0; i <= n; i++) {
			p[i] = i;
			r[i] = 1;
		}
		return new Node;
	}

	int get(int i) {
		return (p[i] == i) ? i : get(p[i]);
	}

	void join(int a, int b) {
		Change* ch = new Change;
		if ( r[a] > r[b]) swap(a, b);
		if ( r[a] == r[b]) {
			ch->b = b;
			ch->r = 1;
			r[b]++;
		}
		ch->a = a;
		ch->p = p[a];
		p[a] = b;
		st.push_back(ch);
	}

	void rollback() {
		Change* ch = st.back();
		if (ch->r)
			r[ch->b]--;
		p[ch->a] = ch->p;
		st.pop_back();
	}

	void dfs(Node* v) {
		if (v->task == '?')
			ans[v->id] = (get(v->a) == get(v->b)) ? 1 : -1;
		if (v->task == '+') {
			int a = get(v->a);
			int b = get(v->b);
			join(a, b);
		}
		for (auto n : v->next) 
			dfs(n);
		if (v->task == '+')
			rollback();		
	}
};

PDSU dsu;

int main() {
	n = readInt();
	k = readInt();
	v[0] = dsu.init(n);
	for(int i = 1; i <= k; i++) {
		v[i] = new Node;
		v[i]->id = i;
		v[i]->task = readChar();
		int j = readInt();
		v[i]->a = readInt();
		v[i]->b = readInt();
		v[j]->next.push_back(v[i]);
	}
	dsu.dfs(v[0]);
	for(int i = 0; i <= k; i++)
		if(ans[i])
			writeWord((ans[i] == 1) ? "YES\n" : "NO\n");
}   





