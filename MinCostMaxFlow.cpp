#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<iomanip>
#include<unordered_map>
#include<unordered_set>
#include<numeric>
#include<list>
 
#define pb push_back
#define all(p) begin(p),end(p)
#define rep(ind,sz) for(int (ind) = 0; (ind) < (sz); (ind)++)
#define vi vector<int>
#define pii pair<int,int>
#define pdd pair<double,double>
#define pll pair<int,int>
#define pss pair<string,string>
#define ve vector
#define mp make_pair
#define PI 3.14159265358979323846
#define int long long
// #define double long double
 
using namespace std;
 
template <class T>
istream& operator >> (istream& in, vector<T>& v) { for (auto& e : v) { in >> e; } return in; }
template <class T>
istream& operator >> (istream& in, pair<T, T>& v) { in >> v.first >> v.second; return in; }
 
template <class T>
ostream& operator << (ostream& out, const vector<T>& v) { for (auto& e : v) { out << e << " "; } out << "\n"; return out; }
template <class T>
ostream& operator << (ostream& out, const pair<T, T>& v) { out << v.first << " " << v.second; return out; }
 
void fast() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
}

void precalc() {}

struct edge {
    int to, cap, flow, cost;
};

ve<edge> edges;
ve<vi> g;
vi p, pe, d;
int s, t;
constexpr int INF = 1e18;

void add_edge(int x, int y, int c, int cost) {
    g[x].push_back(edges.size());
    edges.push_back({y, c, 0, cost});
    g[y].push_back(edges.size());
    edges.push_back({x, 0, 0, -cost});
}

int res(int x) {
    return edges[x].cap - edges[x].flow;
}

void spfa() {
    d.resize(g.size());
    p.resize(g.size());
    pe.resize(g.size());
    rep(i, g.size()) {
        d[i] = INF;
        p[i] = pe[i] = -1;
    }
    vi inq(g.size());
    inq[s] = 1;
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for (int y : g[x]) {
            if (res(y) == 0) continue;
            int to = edges[y].to, w = edges[y].cost;
            if (d[to] > d[x] + w) {
                d[to] = d[x] + w;
                p[to] = x;
                pe[to] = y;
                if (!inq[to]) {
                    inq[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

int augment() {
    if (p[t] == -1) return 0;
    int mf = INF;
    int cur = t;
    while (cur != s) {
        mf = min(mf, res(pe[cur]));
        cur = p[cur];
    }
    cur = t;
    while(cur != s) {
        int e = pe[cur];
        edges[e].flow += mf;
        edges[e ^ 1].flow -= mf;
        cur = p[cur];
    }
    return mf;
}

int maxflow() {
    int ans = 0;
    while (true) {
        spfa();
        int f = augment();
        if (!f) break;
        ans += f * d[t];
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    g.resize(2 * n + 2);
    rep(i, n) {
        rep(j, n) {
            int x;
            cin >> x;
            add_edge(i + 1, j + 1 + n, 1, x);
        }
    }
    s = 0;
    t = 2 * n + 1;
    rep(i, n) {
        add_edge(0, i + 1, 1, 0);
    }
    rep(i, n) {
        add_edge(i + n + 1, t, 1, 0);
    }
    int ans = maxflow();
    cout << ans << '\n';
    for (int i = 1; i <= n; i++){
        for (auto j : g[i]){
            if (j % 2) continue;
            if (edges[j].flow) {
                cout << edges[j].to - n << ' ';
            }
        }
    }
}

signed main() {
#ifdef LOCAL    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fast();
    precalc();
    int t = 1;
    // cin >> t;
    rep(i, t) {
#ifdef LOCAL
        cout << "test case #" << i + 1 << ":\n";
#endif
        solve();   
    }
    return 0;
}