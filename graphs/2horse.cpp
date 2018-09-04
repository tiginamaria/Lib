#include <bits/stdc++.h>
using namespace std;

struct State {
    int x1_ = 0, y1_ = 0, x2_ = 0, y2_ = 0;
    State() {}
    State(const State& st) {
        x1_ = st.x1_;
        y1_ = st.y1_;
        x2_ = st.x2_;
        y2_ = st.y2_;
    }
    State(int x1, int y1, int x2, int y2) : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}
    int hash() {
        return 512 * x1_ + 64 * y1_ + 8 * x2_ + y2_;
    }
};

const int MAXN = 32768;
const int MAXW = 1e9;

queue<State> q;
int d[MAXN];
pair<State,bool> p[MAXN];

vector<int> dx = {1, 1, -1, -1, 2, 2, -2, -2};
vector<int> dy = {2, -2, 2, -2, 1, -1, 1, -1};

char ch1, ch2;
int x1, x2, ay1, y2, x, y;
int sx1, sx2, sy1, sy2;
int fx1, fx2, fy1, fy2;
int hs, hs_to;

vector <pair <int, pair<char,int> > > ans;

int main() {
    ch1 = readChar();
    sx1 = (int)ch1 - (int)'a';
    sy1 = readInt() - 1;

    ch2 = readChar();
    sx2 = (int)ch2 - (int)'a';
    sy2 = readInt() - 1;

    ch1 = readChar();
    fx1 = (int)ch1 - (int)'a';
    fy1 = readInt() - 1;

    ch2 = readChar();
    fx2 = (int)ch2 - (int)'a';
    fy2 = readInt() - 1;

    for (int i = 0; i < MAXN; i++)
        d[i] = MAXW;

    State sst(State(sx1, sy1, sx2, sy2));
    int ssth = sst.hash();

    State fst(State(fx1, fy1, fx2, fy2));
    int fsth = fst.hash();

    d[fsth] = 0;
    q.push(fst);

    while (q.size()) {
        State st(q.front());
        hs = st.hash();
        x1 = st.x1_;
        ay1 = st.y1_;
        x2 = st.x2_;
        y2 = st.y2_;
        q.pop();
        for (size_t i = 0; i < 8; i++) {
            x = x1 + dx[i];
            y = ay1 + dy[i];
            if (x < 8 && x > -1 && y < 8 && y > -1 && !(x1 == x2 && ay1 == y2)) {
                State st_to(State(x, y, x2, y2));
                hs_to = st_to.hash();
                if (d[hs_to] > d[hs] + 1) {
                    d[hs_to] = d[hs] + 1;
                    p[hs_to] = {st, 0};
                    q.push(st_to);
                }
            }
        }
        for (size_t i = 0; i < 8; i++) {
            x = x2 + dx[i];
            y = y2 + dy[i];
            if (x < 8 && x > -1 && y < 8 && y > -1 && !(x1 == x2 && ay1 == y2)) {
                State st_to(State(x1, ay1, x, y));
                hs_to = st_to.hash();
                if (d[hs_to] > d[hs] + 1) {
                    d[hs_to] = d[hs] + 1;
                    p[hs_to] = {st, 1};
                    q.push(st_to);
                }
            }
        }
    }

    int k;
    while (fsth != ssth) {
        k = p[ssth].second;
        State sst(p[ssth].first);
        ssth = sst.hash();
        if (k)
            ans.push_back({k + 1, {(char)(sst.x2_ + 'a'), sst.y2_}});
        else
            ans.push_back({k + 1, {(char)(sst.x1_ + 'a'), sst.y1_}});
    }

    for(size_t i = 0; i < ans.size(); i++) {
        writeInt(ans[i].first,' ');
        writeChar(ans[i].second.first);
        writeInt(ans[i].second.second + 1,'\n');
    }
}







