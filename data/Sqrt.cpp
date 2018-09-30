#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const long long N = 1e6;

int a[N];
vector <int> sorted;
int n, k, m, L, R, X;
char task;

struct Segment {
	int l, r, sz;
	int x;
	Segment (int l, int r) : l(l), r(r), sz(r - l), x(0) {
		for (int  i = l; i < r; i++)
			a[i] = readInt();
		sortSeg();
	}
	
	void inc(int val) {
		x += val;
	}
	
	void sortSeg() {
		for (int i = l; i < r; i++)
			sorted[i] = a[i];
		sort(&sorted[l], &sorted[r]);
	}
	
	void add(int val, int s, int t) {
		while (s <= t)
			a[s] += val, s++;
		sortSeg();
	}
	
	bool findX(int val) {
		//fprintf(stderr, "find %d %d\n", l, r);
		int* pos = lower_bound(&sorted[l], &sorted[r], val - x);
		if(pos != &sorted[r])
			if (*pos + x == val)
				return 1;
		return 0;
	}
	
	bool search(int val, int s, int t) {
		//fprintf(stderr, "search %d %d\n", s, t);
		while (s <= t) {
			if(a[s] + x == val)
				return 1;
			s++;
		}
		return 0;
	}
	
	void printSegA() {
		for (int i = l; i < r; i ++) {
			if (i % k == 0) 
				fprintf(stderr, "   ");
			if (i >= 10)
				fprintf(stderr, "%d  ", a[i] + x);
			else 
				fprintf(stderr, "%d ", a[i] + x);
		}
	}
	void printSegS() {
		for (int i = l; i < r; i ++) {
			if (i % k == 0) 
				fprintf(stderr, "   ");
			if (i >= 10)
				fprintf(stderr, "%d  ", sorted[i] + x);
			else 
				fprintf(stderr, "%d ", sorted[i] + x);
		}
	}
};

vector <Segment> Block;
	
void print_total() {
	for (int i = 0; i < n; i ++) {
		if (i % k == 0) 
			fprintf(stderr, "   ");
		fprintf(stderr, "%d ", i);
	}
	fprintf(stderr, "\n-------------------------------------------------------------------\n");
	for (size_t i = 0; i < Block.size(); i ++)
		Block[i].printSegA();
	
	fprintf(stderr, "\n");
	for (size_t i = 0; i < Block.size(); i ++)
		Block[i].printSegS();
	fprintf(stderr, "\n\n\n");
}

int main() {
	n = readInt();
	m = readInt();
	k = sqrt(n);
	sorted.resize(n + 1);
	for (int i = 0; i < n; i += k)
		Block.push_back(Segment(i, min(i + k, n)));
	//print_total();
	
	for (int j = 0; j < m; j++) {
		task = readChar(), L = readInt() - 1, R = readInt() - 1, X = readInt();
		int i = L / k;
		//fprintf(stderr, "task %c %d %d %d\n", task, L, R, X);
		if (task == '+') {
			Block[i].add(X, L, min(R, Block[i].r - 1)), i++;
				
			while (i < (int)Block.size() && Block[i].r <= R)
				Block[i].inc(X), i++;
			
			if (i < (int)Block.size())
				Block[i].add(X, Block[i].l, R);
		}
		
		if (task == '?') {
			bool res = 0;
			res |= Block[i].search(X, L, min(R, Block[i].r - 1)), i++;
			
			while (i < (int)Block.size() && Block[i].r <= R) {
				res |= Block[i].findX(X), i++;
			}
			
			if (i < (int)Block.size())	
				res |= Block[i].search(X, Block[i].l, R);	
			cout << (res ? "YES" : "NO") << '\n';
			//fprintf(stderr, "%s", res ? "YES\n" : "NO\n");
		}
		//print_total();
	}
}
	





