
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
// heavy store the heavy node of the particular node, parent stores the parent of the node, depth stores the depth of the node starting from the root from 0, leader stores the the particular segment of the tree who is the leader of the node and size stores the size of the subtree of the node including the node itself
v<int> heavy, parent, depth, leader, size;

// With this dfs function we got to know about the heavy node of the particular node, depth of the node, parent of the node and the size of the node including the node itself.
void dfs(int node, v<v<int>> &graph){
    for (auto &child: graph[node]){
        parent[child] = node;
        depth[child] = depth[node] + 1;
        dfs(child, graph);
        size[node] += size[child];
        // The child whose size is great should be the heavy node of the node
        if (size[child] > size[heavy[node]]){
            heavy[node] = child;
        }
    }
    size[node] += 1;
}

// In this function we create the leader of the every node 
// here node represents the node on which we are in and the head represents the leader of the segment in which we are in
void hld(int node, int head, v<v<int>> &graph){
    leader[node] = head;
    // Traversing through the heavy node of the "node"  
    if (heavy[node] != 0){
        hld(heavy[node], head, graph);
    }
    // Traversing through the children of the "node" leaving the heavy node
    for (auto &child: graph[node]){
        if (child != heavy[node]){
            hld(child, child, graph);
        }
    }
}

// This returns the lca of the two node x and y
int solve(int x, int y){
    int ans = 0;
    while(leader[x] != leader[y]){
        if (depth[leader[x]] > depth[leader[y]]){
            // Changing the segment
            x = parent[leader[x]];
        }
        else{
            // Changing the segment
            y = parent[leader[y]];
        }
    }
    if (depth[x] > depth[y]){
        swap(x, y);
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
        depth.assign(n+1, 0);
        parent.assign(n+1, 0);
        size.assign(n+1, 0);
        heavy.assign(n+1, 0);
        leader.assign(n+1, 0);
        for (int i = 1;i <= n;i++){
            int m;
            cin >> m;
            while(m--){
                int a;
                cin >> a;
                graph[i].pb(a);
            }
        }  
        int root = 1;
        // Accumulating the required information about the nodes
        dfs(root, graph);
        hld(root, root, graph);
        int q;
        cin >> q;
        cout << "Case " << (val++) << ":\n";
        // Getting the querys
        while(q--){
            int x, y;
            cin >> x >> y;
            // Solving the query in O(logn^2) time
            int ans = solve(x, y);
            cout << ans << "\n";
        }
        depth.clear();
        parent.clear();
        size.clear();
        heavy.clear();
        leader.clear();
    }
}