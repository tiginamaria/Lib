
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
const int MAXW = 1000000000;
int m[MAXN][MAXN];
int x, n, r = MAXW, d = -MAXW;
int ex[MAXN];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x;
            m[i][j] = (x >= 0) ? x : MAXW;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                m[i][j] = min(m[i][j], m[i][k] + m[k][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ex[i] = (i != j) ? max(ex[i], m[i][j]) : ex[i];

    for (int i = 0; i < n; i++) {
        r = min(r, ex[i]);
        d = max(d, ex[i]);
    }
    cout << d << '\n' << r;
}
