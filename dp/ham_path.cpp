#include <bits/stdc++.h>
#include "optimization.h"
using namespace std;
const int maxn = (1 << 23);
int n, m, z, y, A, best, k;
int endss[maxn];
int g[23];
vector < int > ans;
int cnt[maxn];
int main()
{
    n = readUInt(), m = readUInt();
    for (int i = 0; i < m; i++) {
        z = readUInt(), y = readUInt();
        z--, y--;
        g[y] |= 1 << z;
    }
    g[n] = (1 << n) - 1;

    for (int i = 0; i < n; i++)
        endss[1 << i] = (1 << i);

    for (A = 0; A < (1 << n); A++) {
        cnt[A] = cnt[A >> 1] + (A & 1);
        for (int x = 0; x < n; x++)
            if ((g[x] & endss[A]) && (!(A & (1 << x))))
                endss[A|(1 << x)] |= 1 << x;
    }

    for (A = 0; A < (1 << n); A++) {
        if (endss[A] && cnt[A] > k) {
            k = cnt[A];
            best = A;
        }
    }

    writeInt(k - 1);
    writeChar('\n');
    ans.push_back(n + 1);
    while (k) {
        int j = 0;
        while (!((endss[best] & (1 << j)) & g[ans.back() - 1]))
            j++;
        ans.push_back(j + 1);
        best ^= (1 << j);
        k--;
    }

    while(ans.size() > 1) {
        writeInt(ans.back());
        writeChar(' ');
        ans.pop_back();
    }
}



