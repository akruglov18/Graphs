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


ve<vi> g, gr;
vi order;
vi was, comp;

void ts(int x) {
    was[x] = 1;
    for (int y : g[x]) {
        if (!was[y]) ts(y);
    }
    order.push_back(x);
}

void dfs(int x, int c) {
    comp[x] = c;
    for (int y : gr[x]) {
        if (comp[y] == -1) dfs(y, c);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    was.assign(n, false);
    comp.assign(n, -1);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        g[--a].push_back(--b);
        gr[b].push_back(a);
    }
    rep(i, n) {
        if (!was[i]) ts(i);
    }
    int c = 0;
    rep(i, n) {
        int x = order[n - i - 1];
        if (comp[x] == -1) dfs(x, c++);
    }
    cout << c << "\n";
    rep(i, n) cout << comp[i] + 1 << " ";
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