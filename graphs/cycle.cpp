#include <bits/stdc++.h>
using namespace std;
const int N = 100006;
bool cycle = 1;
stack <long long> st;
long long used[N];
vector <long long> a[N];
vector <long long> c;

void dfs(int x, int p) {
    used[x] = 1;
    st.push(x);
    for (auto to : a[x]) {
        if(used[to] == 1 && to != p) {
            cycle = 0;
            while (st.top()!= to) {
                c.push_back(st.top());
                st.pop();
            }

            c.push_back(to);
            cout  << "YES\n";

            reverse(c.begin(), c.end());
            for (auto v : c)
                cout << v << ' ';
            exit(0);
        } else {
            dfs(to, x);
        }
    }
    if (st.size())
        st.pop();
    used[x] = 2;
}
int main() {
    long long n, m;
    cin >> n >> m;
    long long v, y;
    for(int i = 0; i < m; i++){
        cin >> v >> y;
        a[v].push_back(y);
    }
    for(int i = 0; i < n; i++)
        if (!used[i + 1] && cycle)
            dfs(i + 1, -1);
    if (cycle) {
        cout << "NO\n";
    }
}



