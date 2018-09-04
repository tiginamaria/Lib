#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int MAXK = 150000;
const int MAXN = 50000;

int n, m, k;
int x, y;
char ch[100];
vector<bool> ans;
bool res;
int q[MAXK][3];
int p[MAXN];

void init() {
    for (int i = 0; i < n; i++)
        p[i] = i;
}

int get(int i) {
    return (p[i] == i) ? i : (p[i] = get(p[i]));
}

void join(int a, int b) {
    a = get(a), b = get(b);
    p[a] = b;
}

int main() {
    n = readInt();
    m = readInt();
    k = readInt();
    for (int i = 0; i < m; i++)
        x = readInt(), y = readInt();

    for (int i = k - 1; i >= 0; i--) {
        readWord(ch);
        q[i][0] = (ch[0] == 'a') ? 1 : 0;
        q[i][1] = readInt() - 1;
        q[i][2] = readInt() - 1;
    }

    init();

    for (int i = 0; i < k; i++) {
        if (q[i][0] == 1) {
            res = (get(q[i][1]) == get(q[i][2])) ? 1 : 0;
            ans.push_back(res);
        } else
            join(q[i][1], q[i][2]);
    }

    while (ans.size()) {
        writeWord((ans.back()) ? "YES\n" : "NO\n");
        ans.pop_back();
    }
}   
