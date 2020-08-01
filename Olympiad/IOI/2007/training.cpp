#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gpu_hash_map<int, int> mp;*/
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
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
vector<int> adj[mxN];
ll dp[mxN][1<<10];
ttgl inout[mxN];
int depth[mxN];
int par[mxN][16];
int pid[mxN];
int deg[mxN];
int cnt = 0;
int n, m;
void dfs(int u, int p=0) {
    inout[u].first = cnt++;
    par[u][0] = p;
    for(int v: adj[u]) {
        if(v^p) {
            depth[v] = depth[u]+1;
            pid[v] = 1<<deg[u];
            deg[u]++;
            dfs(v, u);
        }
    }
    inout[u].second = cnt++;
}
int lca(int a, int b) {
    if(depth[a]>depth[b]) {
        uwu(d, 16, 0)if((depth[a]-depth[b])&(1<<d)) a = par[a][d]; 
    }else if(depth[b]>depth[a]) {
        uwu(d, 16, 0)if((depth[b]-depth[a])&(1<<d)) b = par[b][d];
    }
    if(a==b)return a;
    uwu(d, 16, 0) if(par[a][d]!=par[b][d]) {
        a = par[a][d]; b = par[b][d];
    }
    return par[a][0];
}
vector<array<int, 3>> oo;
bool cmp(array<int, 3> a, array<int, 3> b) {
    return inout[lca(a[0], a[1])].second<inout[lca(b[0], b[1])].second;
}
int main() {
    //freopen("greedy.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    ll ans = 0;
    int a, b, c;
    owo(i, 0, m) {
        cin>>a>>b>>c;
        a--; b--;
        ans+=c;
        if(c==0) {
            adj[a].senpai(b);
            adj[b].senpai(a);
        }
        oo.senpai({a, b, c});
    }
    dfs(0);
    owo(lg, 1, 16) {
        owo(i, 0, n) {
            par[i][lg] = par[par[i][lg-1]][lg-1];
        }
    }
    sort(oo.begin(), oo.end(), cmp);
    for(auto p: oo) {
        int node = lca(p[0], p[1]);
        if(p[2]&&((depth[p[1]] + depth[p[0]] - 2*depth[node])&1)) {
            continue;
        }
        int val = p[2];
        ttgl up1 = {p[0], 0};
        while(up1.first!=node) {
            val+=dp[up1.first][up1.second];
            up1.second = pid[up1.first];
            up1.first = par[up1.first][0];
        }
        ttgl up2 = {p[1], 0};
        while(up2.first!=node) {
            val+=dp[up2.first][up2.second];
            up2.second = pid[up2.first];
            up2.first = par[up2.first][0];
        }
        for(int msk = (1<<deg[node])-1; ~msk; --msk) {
            if(!(msk&up1.second||msk&up2.second)) {
                dp[node][msk] = max(dp[node][msk], val + dp[node][msk|up1.second|up2.second]);
            }
        }
    }
    cout<<(ans-dp[0][0])<<"\n";
    return 0;
}
