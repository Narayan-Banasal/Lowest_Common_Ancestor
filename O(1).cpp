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
// lt is used to store the nodes of the tree in the linearize manner so that query on the lt is got easy, start is to store the time of the node(index) in the linearized tree where the particular node gets into dfs traversal, depth to store the depth of the node, temp_log is to store the logrithmic value of the value.
v<int> lt, start, depth, temp_log;
// Sparse table is to store the node whose depth is minimum in the particular range
v<v<int>> sparse;

// To the populate the start vector, depth vector and lt vector
void dfs(int node, v<v<int>> &graph){
    start[node] = lt.size();
    lt.pb(node);
    for (int i: graph[node]){
        depth[i] = depth[node] + 1;
        dfs(i, graph);
        lt.pb(node);
    }
}

// Build the sparse table based on the depth of the node from the root
void build(){
    int mx_bit = 0;
    while((1 << mx_bit) <= lt.size())    mx_bit += 1;
    sparse = v<v<int>> (lt.size(), v<int> (mx_bit));

    for (int i = 0;i < lt.size();i++){
        sparse[i][0] = lt[i];
    }

    for (int j = 1;j < mx_bit;j++){
        for (int i = 0;(i + (1 << j)) < lt.size();i++){
            int x = sparse[i][j-1];
            int y = sparse[i+(1<<(j-1))][j-1];

            sparse[i][j] = (depth[x] < depth[y]) ? x : y;
        }
    }
}

// Get the lca in the O(1) time
int rangeQuery(int l, int r){
    int val = r-l;
    int temp_log_val = temp_log[val];
    int val1 = sparse[l][temp_log_val];
    int val2 = sparse[r - (1 << temp_log_val) + 1][temp_log_val];

    return (depth[val1] < depth[val2] ? val1 : val2);
}

// Building the logrithmic value of the value
void build_temp_log(){
    temp_log.resize(5000);
    temp_log[0] = 0, temp_log[1] = 0;
    for (int i = 2;i < 5000;i++){
        temp_log[i] = temp_log[i/2] + 1;
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1, val = 1;
    cin >> t;
    build_temp_log();
    while(t--){
        int n; 
        cin >> n;
        v<v<int>> graph(n+1);
        start.assign(n+1, 0);
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
        // Accumulating the required information about the nodes
        dfs(1, graph);
        build();
        int q;
        cin >> q;
        cout << "Case " << (val++) << ":\n";
        while(q--){
            int x, y;
            cin >> x >> y;
            // To get the lca of the nodes in the constant time
            int ans = rangeQuery(min(start[x], start[y]), max(start[x], start[y]));
            cout << ans << "\n";
        }
        lt.clear();
        start.clear();
        depth.clear();
        sparse.clear();
    }   
}