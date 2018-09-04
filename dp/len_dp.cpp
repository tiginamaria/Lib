#include <bits/stdc++.h>

using namespace std;

const int MAXN = 21;

int n, m, k, buy;

int mask[200];
int cost[200];
int dp[1 << MAXN];


int main() {

    int x;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        mask[i] = 1 << i;
        cost[i] = x;
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> cost[n + i];
        cin >> k;
        int add = 0;
        for (int j = 0; j < k; j++) {
            cin >> x; --x;
            add |= 1 << x;
        }
        mask[n + i] = add;
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> x; --x;
        buy |= 1 << x;
    }

    for (int i = 0; i < (1 << n); i++) {
        dp[i] = INT_MAX - 10000;
    }
    dp[0] = 0;

    for (int i = 0; i < n + m; i++)
        if (mask[i] & buy)
            for (int A = 0; A < (1 << n); A++)
                if (dp[A] + cost[i] < dp[A | mask[i]])
                    dp[A | mask[i]] = dp[A] + cost[i];

    int c = dp[buy];
    for (int A = 1; A < (1 << n); A++)
        if ((buy | A) == A)
            c = min(c, dp[A]);
    cout << c;
}



