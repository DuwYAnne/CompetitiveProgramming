#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/extc++.h>
#define owo(i,a, b) for(auto i=(a);i<(b); ++i)
#define uwu(i,a, b) for(auto i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
using namespace std;
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 501;
int n, m, r, t, k;
int cnt;
int numused[mxN];
vector<int> adj[mxN];
bool used[mxN];
int prv[mxN];
int typ1[mxN];
int typ2[mxN];
bool dfs(int u) {
    if(typ1[u]==cnt)return false;
    typ1[u] = cnt;
    for(int v: adj[u]) {
        if(typ2[v]==cnt)continue;
        typ2[v] = cnt;
        if(prv[v] == -1 || dfs(prv[v])) {
            prv[v] = u;
            return true;
        }
    }
    return false;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>r>>t>>k;
    int most = min(t/r, m);
    pair<int, ll> res;
    memset(prv, -1, sizeof(prv));
    int a, b;
    owo(i, 0, k) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
    }
    owo(i, 0, most) {
        owo(j, 0, n) {
            if(used[j])continue;
            cnt++;
            if(dfs(j)) {
                res.second += (i+1) * r;
                res.first++;
            }else {
                used[j] = true;
            }
        }
    }
    cout<<res.first<<" "<<res.second<<"\n";
    owo(i, 0, m) {
        if(prv[i]!=-1) {
            cout<<(prv[i] + 1)<<" "<<(i + 1)<<" "<<(r * numused[prv[i]]++)<<"\n";
        }
    }
    return 0;
}
