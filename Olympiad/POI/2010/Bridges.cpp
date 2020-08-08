//#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
gpu_hash_table<int, int> mp;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 */
using ll = long long;
using ld = long double;
const ll MOD = 924844033;
const ll root = 62;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 1001;
array<int, 4> all[2*mxN];
vector<int> ans[mxN];
int back[2*mxN][2*mxN];
int deg[mxN];
int n, m;
struct Edge {
    int v, u;
    ll cap, flow = 0;
    Edge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    vector<Edge> edges;
    vector<vector<int>> adj;
    int N, M = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
    Dinic(int nn, int s, int t) : N(nn), s(s), t(t) {
        adj.resize(nn);
        level.resize(nn);
        ptr.resize(nn);
    }

    void addEdge(int v, int u, ll cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(M);
        adj[u].push_back(M + 1);
        M += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, INFLL)) {
                f += pushed;
            }
        }
        return f;
    }
    void restore() {
        for(auto e: edges) {
            //cout<<e.v<<" "<<e.u<<" "<<e.flow<<" "<<all[e.u-n-1][0]<<" "<<all[e.u-n-1][1]<<"\n";
            if(e.flow==1&&e.u>n&&e.u<n+m+1) {
            //cout<<e.u<<" "<<e.v<<" "<<e.flow<<" "<<all[e.v-n-1][0]<<" "<<all[e.v-n-1][1]<<"\n";
                int u = e.u-n-1;
                if(e.v==all[u][0]) {
                    ans[e.v].senpai(all[u][1]);
                }else {
                    ans[e.v].senpai(all[u][0]);
                }
            }
        }
    }
};
bool check(int k, bool last) {
    Dinic graph(n+m+2, 0, n+m+1);
    owo(i, 1, n+1) {
        graph.addEdge(0, i, deg[i]/2);
    }
    owo(i, 0, m) {
        if(all[i][2]>k&&all[i][3]>k)return false;
        if(all[i][2]<=k) {
            graph.addEdge(all[i][0], n+i+1, 1);
            /*if(last&&all[i][3]>k) {
                ans[all[i][0]].senpai(all[i][1]);
            }*/
        }
        if(all[i][3]<=k) {
            graph.addEdge(all[i][1], n+i+1, 1);
            /*if(last&&all[i][2]>k) {
                ans[all[i][1]].senpai(all[i][0]);
            }*/
        }
        graph.addEdge(n+i+1, n+m+1, 1);
    }
    int res = graph.flow();
    if(last)graph.restore();
    return res==m;
}
void dfs() { 
    unordered_map<int,int> edge_count; 
  
    owo(i, 1, n+1) {
        edge_count[i] = ans[i].size(); 
    }
  
    stack<int> curr_path; 
    vector<int> circuit; 
    curr_path.push(1); 
    int curr_v = 1;
    while (!curr_path.empty()) { 
        if (edge_count[curr_v]) { 
            curr_path.push(curr_v); 
            int next_v = ans[curr_v].back(); 
            edge_count[curr_v]--; 
            ans[curr_v].pop_back(); 
            curr_v = next_v; 
        } 
        else{ 
            circuit.push_back(curr_v); 
            curr_v = curr_path.top(); 
            curr_path.pop(); 
        } 
    } 
  
    // we've got the circuit, now print it in reverse 
    for (int i=circuit.size()-2; i>=0; i--) { 
        cout<<back[circuit[i+1]][circuit[i]]<<" ";
    } 
} 
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b, c, d;
    owo(i, 0, m) {
        cin>>a>>b>>c>>d;
        deg[a]++;
        deg[b]++;
        back[a][b] = i+1;
        back[b][a] = i+1;
        all[i] = {a, b, c, d};
    }
    owo(i, 1, n+1) {
        if(deg[i]&1) {
            cout<<"NIE\n";
            exit(0);
        }
    }
    int l = 0;
    int r = 1000;
    while(l<r) {
        int mid = (l+r)/2;
        if(check(mid, false))r = mid;
        else l =mid+1;
    }
    cout<<l<<"\n";
    check(l, true);
    /*owo(i, 0, n+1) {
        cout<<i<<"\n";
        for(auto p: ans[i]) {
            cout<<p<<" ";
        }
        cout<<"\n";
    }*/
    dfs();
    return 0;
}
