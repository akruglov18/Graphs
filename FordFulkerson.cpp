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
vi was;
int s, t;
 
void add_edge(int x, int y, int c) {
    g[x].push_back(edges.size());
    edges.push_back({y, c, 0});
    g[y].push_back(edges.size());
    edges.push_back({x, 0, 0});
}
 
int res(int x) {
    return edges[x].capacity - edges[x].flow;
}
 
int dfs(int x, int f) {
    if (x == t) return f;
    if (was[x]) return 0;
    was[x] = 1;
    for (int y : g[x]) {
        int r = res(y);
        if (r == 0) continue;
        int pushed = dfs(edges[y].to, min(r, f));
        if (pushed) {
            edges[y].flow += pushed;
            edges[y ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
 
int mf() {
    int res = 0;
    while (true) {
        was.assign(g.size(), false);
        int f = dfs(s, 1e18);
        if (!f) break;
        res += f;
    }
    return res;
}
 
void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        add_edge(a, b, c);
        // add_edge(b, a, c);
    }
    s = 0, t = n - 1;
    cout << mf() << "\n";
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