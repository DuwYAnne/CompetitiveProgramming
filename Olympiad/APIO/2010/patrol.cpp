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
const int mxN = 100001;
int n, k;
vector<int> adj[mxN];
int dp[mxN][3];
int depth[mxN];
int mxd[mxN];
//dp0 = one path in subtree
//dp1 = one path in subtree with unclosed other path
//dp2 = two paths in subtree
void solve(int u, int p) {
    mxd[u] = depth[u];
    vector<ttgl> alld;
    vector<ttgl> alla;
    for(int v: adj[u]) {
        if(v^p) {
            depth[v] = depth[u] + 1;
            solve(v, u);
            mxd[u] = max(mxd[u], mxd[v]);
            owo(i, 0, 3) {
                dp[u][i] = max(dp[u][i], dp[v][i]);
            }
            alld.senpai({mxd[v], v});
            alla.senpai({dp[v][0], v});
        }
    }
    sort(alld.begin(), alld.end(), greater<ttgl>());
    sort(alla.begin(), alla.end(), greater<ttgl>());
    //dumb casework
    if(adj[u].size()>2||(adj[u].size()==2&&u==0)) {
        dp[u][0] = max(dp[u][0], alld[0].first + alld[1].first - 2*depth[u]);
        dp[u][2] = max(dp[u][2], alla[0].first + alla[1].first);
        //try building 2 paths with 1 and unclosed
        for(int v: adj[u]) {
            if(v^p) {
                int pathL = alld[0].first;
                if(v==alld[0].second) {
                    pathL = alld[1].first;
                }
                dp[u][1] = max(dp[u][1], pathL + dp[v][0]);
                dp[u][2] = max(dp[u][2], dp[v][1] + pathL - 2*depth[u]);
                if(adj[u].size()>3) {
                    int cnt = 0;
                    pathL = 0;
                    for(int i=0; cnt<2; ++i) {
                        if(alld[i].second==v)continue;
                        cnt++;
                        pathL+=alld[i].first;
                    }
                    dp[u][2] = max(dp[u][2], pathL + dp[v][0] - 2*depth[u]);
                }
            }
        }
    }
    if(adj[u].size()>3||(adj[u].size()==3&&u==0)) {
        dp[u][1] = max(dp[u][1], alld[0].first + alld[1].first + alld[2].first - 2*depth[u]);
    }
    if(adj[u].size()>4||(adj[u].size()==4&&u==0)) {
        dp[u][2] = max(dp[u][2], alld[0].first + alld[1].first + alld[2].first + alld[3].first - 4*depth[u]);
    }
    //cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<" "<<dp[u][2]<<"\n";
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    solve(0, 0);
    if(k==1) {
        cout<<(2*n-2-dp[0][0] + 1)<<"\n";
    }else {
        cout<<(2*n-2-dp[0][2] + 2)<<"\n";
    }
    return 0;
}
