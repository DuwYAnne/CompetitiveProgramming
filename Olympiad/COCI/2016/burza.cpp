#pragma GCC target ("avx2")
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
const int mxN = 401;
int timer = 1;
ttgl inout[mxN];
vector<int> nodes[21];
int dp[1<<20];
int depth[mxN];
int n, k;
vector<int> adj[mxN];
void dfs(int u=0, int p=0) {
    if(depth[u]==k) {
        inout[u].first = timer;
        inout[u].second = timer++;
        nodes[k-1].senpai(u);
        return;
    }
    inout[u].first = INF;
    inout[u].second = 0;
    for(int v: adj[u]) {
        if(v^p) {
            depth[v] = depth[u]+1;
            dfs(v, u);
            inout[u].first = min(inout[u].first, inout[v].first);
            inout[u].second = max(inout[u].second, inout[v].second);
        }
    }
    if(inout[u].first!=INF) {
        nodes[depth[u]-1].senpai(u);
    }
}
bool solve() {
    owo(msk, 0, 1<<k) {
        int farthest = dp[msk];
        owo(bit, 0, k) {
            if(msk&(1<<bit))continue;
            dp[msk^(1<<bit)] = max(dp[msk^(1<<bit)], dp[msk]);
            for(int u: nodes[bit]) {
                //cout<<u<<" "<<inout[u].first<<" "<<inout[u].second<<" hi\n";
                if(inout[u].first<=farthest+1&&inout[u].second>farthest) {
                    dp[msk^(1<<bit)] = max(dp[msk^(1<<bit)], inout[u].second);
                    //cout<<u<<" "<<dp[msk^(1<<bit)]<<" "<<(msk^(1<<bit))<<"\n";
                }
            }
        }
        if(dp[msk]>=timer-1) return true;
    }
    return false;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    if(k*k>n) {
        cout<<"DA\n";
        exit(0);
    }
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    dfs();
    cout<<(solve() ? "DA\n" : "NE\n");
    return 0;
}
