#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mod 1000000007
#define um unordered_map
#define us unordered_set
#define f first
#define s second
#define v vector
#define all(arr) arr.begin(), arr.end()
template <typename T> istream& operator>>(istream &istream, vector<T> &nums){ for(auto &val: nums) cin >> val; return istream;}
template <typename T1, typename T2> istream& operator>>(istream &istream, pair<T1, T2> &p){ return (istream >> p.f >> p.s);}
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...);}
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')';}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NONI_DEBUG 
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// Used to store the parent of the node and the depth of the node from the root starting from 0
v<int> parent, depth;

// Getting the parent and node of the node
void dfs(int node, v<v<int>> &graph){
    for (auto &child: graph[node]){
        parent[child] = node; 
        depth[child] = depth[node] + 1;
        dfs(child, graph);
    }
}

// Returns the lowest common ancestor of the two nodes by moving one by one to the parent untill they meet at the common node
int lca(int x, int y){
    if (depth[x] < depth[y]) swap(x, y);
    int dis = depth[x] - depth[y];
    while(depth[x] != depth[y]){
        x = parent[x];
        dis--;
    }
    if (x == y) return x;
    while(x != y){
        x = parent[x];
        y = parent[y];
    }
    return x;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1, val = 1;
    cin >> t;
    while(t--){
        int n; 
        cin >> n;
        v<v<int>> graph(n+1);
        parent.assign(n+1, 0);
        depth.assign(n+1, 0);
        for (int i = 1;i <= n;i++){
            int m;
            cin >> m;
            while(m--){
                int a;
                cin >> a;
                graph[i].pb(a);
            }
        }  
        dfs((int)1, graph);
        int q;
        cin >> q;
        cout << "Case " << (val++) << ":\n";
        while(q--){
            int x, y;
            cin >> x >> y;
            
            int ans = lca(x, y);
            cout << ans << "\n";
        }
        parent.clear();
        depth.clear();
    }
}