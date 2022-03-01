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
// depth is to store the depth of the node from the root starting from the 0, parent is to store the parent of the node and lg is for storing the value of the logarithm of the number of nodes in the tree
v<int> depth, parent, lg;
// This is the sparse table which helps to resolve the query in O(logn) time
v<v<int>> sparse;

// Getting the parent and node of the node in the tree
void dfs(int node, v<v<int>> &graph){
    for (int i: graph[node]){
        depth[i] = depth[node] + 1;
        parent[i] = node;
        dfs(i, graph);
    }
}

// function to store the log2 value of the value
void create_log(){ 
    lg.assign(1005, 0);
    for (int i = 2;i<1005;i++){
        lg[i] = lg[i/2] + 1;
    }
}

// Creating of the sparse table which stores the parent of the node according to the depth of the node 
void create_sparse(int n){ 
    int k = lg[n] + 1;
    sparse = v<v<int>> (n+1, v<int> (k+1, 0));
    for (int i = 1;i <= n;i++){
        sparse[i][0] = parent[i];
    }

    for (int j = 1;j <= k;j++){
        for (int i = 1;i <= n;i++){
            sparse[i][j] = sparse[sparse[i][j-1]][j-1];
        }
    }
}

// Where the answer to the particular query is provided in O(logn) time
int solve(int a, int b){
    if (depth[a] < depth[b]){
        swap(a, b);
    }

    int diff = depth[a] - depth[b];
    int k = lg[diff]+1;
    for (int i = k-1;i >= 0;i--){
        if (diff & (1 << i)){
            a = sparse[a][i];
        }
    }

    if (a == b){
        return a;
    }
    int x = lg[depth[a]];
    for (int i = x;i >= 0;i--){
        if (sparse[a][i] != sparse[b][i]){
            a = sparse[a][i];
            b = sparse[b][i];
        }
    }
    return parent[a];
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    int val = 1;
    create_log();

    while(t--){
        int n; 
        cin >> n;
        v<v<int>> graph(n+1);
        depth.assign(n+1, 0);
        parent.assign(n+1, 0);
        for (int i = 1;i <= n;i++){
            int m;
            cin >> m;
            while(m--){
                int a;
                cin >> a;
                graph[i].pb(a);
            }
        }
        // Accumulating the required information about the nodes
        dfs(1, graph);
        create_sparse(n);
        
        int q;
        cin >> q;
        cout << "Case " << (val++) << ":\n";
        while(q--){
            int x, y;
            cin >> x >> y;
            // Solving the query in O(logn) time
            int ans = solve(x, y);
            cout << ans << "\n";
            
        }
        parent.clear();
        depth.clear();
        sparse.clear();
    }   
}