//#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define owo(i,a, b) for(auto i=(a);i<(b); ++i)
#define uwu(i,a, b) for(auto i=(a)-1; i>=(b); --i)
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
const int mxN = 50001;
const int logn = 21;
int ans[mxN];
int dp[mxN][logn];
int n;
vector<int> adj[mxN];
int res = 0;
void dfs(int u, int p = -1) {
    for(int v: adj[u]) {
        if(v^p) {
            dfs(v, u);
            owo(i, 0, logn) {
                dp[u][i]+=dp[v][i];
            }
        }
    }
    int curr = logn-1;
    while(curr&&dp[u][curr]<2)curr--;
    while(dp[u][curr])curr++;
    ans[u] = curr;
    dp[u][curr] = 1;
    while(curr)dp[u][--curr] = 0;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    dfs(0);
    owo(i, 0, n) {
        res = max(res, ans[i]);
    }
    cout<<res<<"\n";
    return 0;
}
