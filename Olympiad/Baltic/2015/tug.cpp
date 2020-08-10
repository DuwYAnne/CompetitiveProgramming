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
const ll MOD = 998244353;
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
const int mxN = 30001;
//remove 0/1 spot stuff
//everything left has 2 possible people
//decompose into graph and do knapsack
multiset<ttgl> adj[2*mxN];
int deg[2*mxN];
bitset<40*mxN> dp;
int n, k;
int dfs(int u) {
    int res = 0;
    if(adj[u].size()) {
        auto nxt = *adj[u].begin();
        res+=nxt.second * (u<n ? 1 : -1);
        adj[u].erase(adj[u].find(nxt));
        adj[nxt.first].erase(adj[nxt.first].find({u, nxt.second}));
        res+=dfs(nxt.first);
    }
    return res;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    int a, b, c;
    owo(i, 0, 2*n) {
        cin>>a>>b>>c;
        a--; b--;
        b+=n;
        adj[a].insert({b, c});
        adj[b].insert({a, c});
        deg[a]++; deg[b]++;
    }
    int mid = 20*n;
    queue<int> Q;
    owo(i, 0, 2*n) {
        if(deg[i]==0) {
            cout<<"NO\n";
            exit(0);
        }
        if(deg[i]==1) {
            Q.push(i);
        }
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if(adj[u].size()==0) {
            cout<<"NO\n";
            exit(0);
        }
        ttgl nxt = *adj[u].begin();
        mid+=nxt.second * (u<n ? 1 : -1);
        adj[nxt.first].erase(adj[nxt.first].find({u, nxt.second}));
        if(adj[nxt.first].size()==1) Q.push(nxt.first);
    }
    vector<int> kk;
    owo(i, 0, 2*n) {
        if(adj[i].size()<=1)continue;
        int nxt = dfs(i);
        if(nxt<0)nxt*=-1;
        mid-=nxt;
        kk.senpai(2*nxt);
    }
    dp[mid] = 1;
    for(int p: kk) {
        dp|=dp<<p;
    }
    bool ok = false;
    owo(i, 20*n-k, 20*n+k+1) {
        ok|=dp[i];
        if(ok)break;
    }
    cout<<(ok ? "YES\n" : "NO\n");
    return 0;
}
