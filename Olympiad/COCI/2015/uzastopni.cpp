#pragma GCC target ("avx2")
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
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 10001;
const int mxV = 103;
vector<int> adj[mxN];
int arr[mxN];
bitset<mxV> dp[mxN][mxV]; // dp[i][l][r] = possible
bitset<mxV> lft[mxN];
int n;
void solve(int u, int p = -1) {
    vector<int> c;
    for(int v: adj[u]) {
        if(v^p) {
            solve(v, u);
            c.senpai(v);
        }
    }
    sort(c.begin(), c.end(), [&](int a, int b) {
        return arr[a] < arr[b];
    });
    owo(i, 0, c.size()) {
        owo(r, 0, mxV) {
            owo(l, 1, r+1){
                if(dp[c[i]][r][l]) {
                    lft[r]|= lft[l-1];
                }
            }
            lft[r]|=dp[c[i]][r];
        }
    }
    dp[u][arr[u]][arr[u]] = 1;
    dp[u][arr[u]]|=lft[arr[u]-1];
    owo(r, arr[u]+1, mxV) {
        if(lft[r][arr[u]+1]) {
            dp[u][r]|=lft[arr[u]-1];
            dp[u][r][arr[u]] = 1;
        }
    }
    owo(i, 0, mxV) {
        lft[i].reset();
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i];
    }
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    solve(0);
    int ans = 0;
    owo(r, 0, mxV){
        ans+=dp[0][r].count();
    }
    cout<<ans<<"\n";
    return 0;
}
