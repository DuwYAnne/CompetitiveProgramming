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
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 500001;
vector<int> adj[mxN];
int tin[mxN];
int low[mxN];
int par[mxN];
vector<ttgl> st;
vector<int> g[mxN];
int deg[mxN];
int dist[mxN];
int cnt = 0;
int n, m;
int len = -1;
ll ans = 0;
void bad() {
    cout<<"NIE\n";
    exit(0);
}
int check(int u, int v) {
    queue<int> Q;
    Q.push(u);
    dist[u] = 0;
    while(!Q.empty()) {
        int a = Q.front();
        Q.pop();
        for(int i: g[a]) {
            if(i==v) {
                if(dist[i]==-1) {
                    dist[i] = dist[a]+1;
                }
                if(dist[i]!=dist[a]+1)bad();
            }else {
                if(dist[i]==-1) {
                    dist[i] = dist[a]+1;
                    Q.push(i);
                }
            }
        }
    }
    return dist[v]*2;
}
void solve(vector<ttgl> &edges) {
    if(edges.size()==1)return;
    vector<int> nodes;
    for(auto p: edges) {
        g[p.first].senpai(p.second);
        g[p.second].senpai(p.first);
        nodes.senpai(p.first);
        nodes.senpai(p.second);
        deg[p.first]++;
        deg[p.second]++;
    }
    sort(nodes.begin(), nodes.end());
    nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());
    vector<int> ends;
    for(int k: nodes) {
        if(deg[k]>2) {
            ends.senpai(k);
        }
        dist[k] = -1;
    }
    if(ends.size()==0) {
        int currlen = nodes.size();
        if(len==-1)len = currlen;
        if(currlen!=len)bad();
        ans = (ans + 1)%MOD;
    }else if(ends.size()==2) {
        int u = ends[0];
        int v = ends[1];
        int currlen = check(u, v);
        if(len==-1)len = currlen;
        if(currlen!=len)bad();
        ans = (ans + 1LL*deg[u]*(deg[u]-1)/2)%MOD;
    }else bad();
    for(int k: nodes) {
        g[k].clear();
        deg[k] = 0;
    }
}
void get(int u, bool root = 0) {
    tin[u]=low[u] = cnt++;
    int child = 0;
    for(int v: adj[u]) {
        if(v==par[u])continue;
        if(tin[v]==-1) {
            child++;
            par[v] = u;
            st.senpai({u, v});
            get(v);
            low[u] = min(low[v], low[u]);
            if((root&&child>1)||(!root&&tin[u]<=low[v])) {
                vector<ttgl> temp;
                while(st.back()!=(ttgl{u, v})) {
                    temp.senpai(st.back()); 
                    //cout<<st.back().first<<" "<<st.back().second<<"\n";
                    st.pop_back();
                }
                //cout<<st.back().first<<" "<<st.back().second<<"\n";
                temp.senpai(st.back()); st.pop_back();
                solve(temp);
                temp.clear();
                //fin.senpai(temp);
            }
        }else if(tin[v]<=tin[u]){
            low[u] = min(tin[v], low[u]);
            st.senpai({u, v});
        }
    }
}
void bcc() {
    memset(par, -1, sizeof(par));
    memset(low, -1, sizeof(low));
    memset(tin, -1, sizeof(tin));
    owo(i, 0, n) {
        if(tin[i]==-1) {
            get(i, 1);
            solve(st);
            st.clear();
        }
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    if(m==n-1) {
        cout<<"BRAK\n";
        exit(0);
    }
    int a, b;
    owo(i, 0, m) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    bcc();
    //cout<<ans<<"\n";
    cout<<"TAK\n";
    ans =(ans * len * 2)%MOD;
    cout<<len<<" "<<ans<<"\n";
    return 0;
}
