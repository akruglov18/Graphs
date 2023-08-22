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
    int to, capacity, flow;
};
 
ve<vi> g;
ve<edge> edges;
vi d, lst;
int s, t, k;
constexpr int INF = 1e18;
 
void add_edge(int x, int y, int c) {
    g[x].push_back(edges.size());
    edges.push_back({y, c, 0});
    g[y].push_back(edges.size());
    edges.push_back({x, 0, 0});
}
 
int res(int x) {
    return edges[x].capacity - edges[x].flow;
}
 
bool bfs() {
    d.resize(g.size());
    rep(i, g.size()) d[i] = INF;
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : g[x]) {
            if (res(y) == 0) continue;
            int to = edges[y].to;
            if (d[to] > d[x] + 1) {
                d[to] = d[x] + 1;
                q.push(to);
            }
        }
    }
    if (d[t] == INF) return false;
    return true;
}
 
int dfs(int x, int flow) {
    if (x == t) return flow;
    int sum = 0;
    for (; lst[x] < g[x].size(); lst[x]++) {
        int e = g[x][lst[x]];
        int r = res(e);
        int to = edges[e].to;
        if (r == 0 || d[to] != d[x] + 1) continue;
        int pushed = dfs(to, min(flow - sum, r));
        sum += pushed;
        edges[e].flow += pushed;
        edges[e ^ 1].flow -= pushed;
        if (sum == flow) break;
    }
    return sum;
}
 
int dinic() {
    int res = 0;
    while (true) {
        if (!bfs()) break;
        lst.assign(g.size(), 0);
        while (true) {
            int pushed = dfs(s, INF);
            if (!pushed) break;
            res += pushed;
        }
    }
    return res;
}
 
void solve() {
    int n;
    cin >> n;
    g.resize(n);
    rep(i, n) {
        rep(j, n) {
            int c;
            cin >> c;
            add_edge(i, j, c);
        }
    }
    s = 0, t = n - 1;
    cout << dinic() << "\n";
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