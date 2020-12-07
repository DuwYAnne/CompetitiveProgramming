/*
Consider the solution where we have just paths of length <= t. We can solve this version with matrix multiplication easily. Then,
we can expand this recurrence to certain edges of length 2, and use inclusion-exclusion over the characters to solve.
*/


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
const ll MOD = 5557;
const ll root = 62;
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 25;
int adj[mxN][mxN];
struct M {
    const static int n = 51;
    ll m[n][n];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M& m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res.m[i][j] += m[i][a] * m2.m[a][j];
                    if (res.m[i][j] >= MOD) res.m[i][j] %= MOD;
                }
            }
        }
        return res;
    }
};
M I() {
    M m;
    for (int i = 0; i < 51; i++) m.m[i][i] = 1;
    return m;
}
void bpow(M &m, ll e) {
    M res = I();
    while (e) {
        if (e & 1) res = res * m;
        m = m * m;
        e >>= 1;
    }
    m = res;
}
int n, m;
ll t;
ll solve(int msk) {
    M a, b;
    owo(i, 0, n) {
        b.m[2*i][2*i+1] = 1;
        owo(j, 0, n) {
            if(adj[i][j]) {
                b.m[2*i][2*j] = 1;
                if(adj[i][j] && ((msk & adj[i][j])==0)) b.m[2*i+1][2*j] = 1;
            }
        }
    }
    b.m[0][2*n] = 1;
    b.m[2*n][2*n] = 1;
    a.m[0][0] = 1;
    bpow(b, t);
    a = a*b;
    return (a.m[0][0] + a.m[0][2*n])%MOD;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b;
    string s;
    owo(i, 0, m) {
        cin>>a>>b>>s;
        a--; b--;
        for(auto c: s) {
            if(c=='M')adj[a][b]+=1;
            if(c=='J')adj[a][b]+=2;
            if(c=='B')adj[a][b]+=4;
            if(c=='P')adj[a][b]+=8;
        }
    }
    cin>>t;
    ll ans = 0;
    owo(msk, 0, 1<<4) {
        int parity = __builtin_popcount(msk)&1 ? -1 : 1;
        //cout<<solve(msk)<<"\n";
        ans = (ans + parity*solve(msk))%MOD;
        if(ans < 0)ans+=MOD;
    }
    cout<<ans<<"\n";
    return 0;
}
