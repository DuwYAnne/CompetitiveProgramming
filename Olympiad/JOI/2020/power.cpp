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
const ll MOD = 1000000007;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 200001;
vector<int> adj[mxN];
int arr[mxN];
int ans = 0;
int dp[mxN];
string s;
int n;
void dfs(int u, int p = -1) {
    if(arr[u]) {
        int best = 0;
        for(int v: adj[u]) {
            if(v^p) {
                dfs(v, u);
                dp[u]+=dp[v];
                best = max(best, dp[v]);
            }
        }
        ans = max(ans, best + 1);
        dp[u]--;
        dp[u] = max(dp[u], 1);
    }else {
        for(int v: adj[u]) {
            if(v^p) {
                dfs(v, u);
                dp[u]+=dp[v];
            }
        }
    }
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
    cin>>s;
    owo(i, 0, n) {
        arr[i] = s[i]=='1';
    }
    dfs(0);
    owo(i, 0, n) {
        ans = max(ans, dp[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
