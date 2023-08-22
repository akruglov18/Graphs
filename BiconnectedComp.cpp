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


ve<vi> g;
vi up, was, d;
ve<pii> e;
ve<ve<pii>> comp;
vi st;

void add_comp(int sz) {
    comp.push_back({});
    while (st.size() > sz) {
        comp.back().push_back(e[st.back()]);
        st.pop_back();
    }
}

void dfs(int x, int p = -1) {
    up[x] = d[x];
    was[x] = 1;
    int cnt = 0;
    for (int i : g[x]) {
        int y = e[i].first ^ e[i].second ^ x;
        if (y == p) continue;
        if (!was[y]) {
            cnt++;
            d[y] = d[x] + 1;
            int sz = st.size();
            st.push_back(i);
            dfs(y, x);
            if (up[y] >= d[x]) {
                add_comp(sz);
            }
            up[x] = min(up[x], up[y]);
        } else {
            if (d[x] > d[y]) st.push_back(i);
            up[x] = min(up[x], d[y]);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    was.assign(n, false);
    up.assign(n, 1e9);
    d.assign(n, 0);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(i);
        g[b].push_back(i);
        e.push_back({a, b});
    }
    rep(i, n) {
        if (!was[i]) dfs(i);
    }
    cout << comp.size() << "\n";
    for (auto &v : comp) {
        cout << v.size() << "\n";
        for (auto &x : v) {
            cout << x.first + 1 << " " << x.second + 1 << "\n";
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