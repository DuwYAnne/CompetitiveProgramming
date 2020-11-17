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
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 200001;
int n;
int val[mxN];
int dsu[mxN];
bool done[mxN];
vector<int> adj[mxN];
int cnt[mxN][30][2];
int sz[mxN];
int ord[mxN];
ll sub[30][2];
ll p2[mxN];
ll ans = 0;
int find(int a) {
    return dsu[a] == a ? a : dsu[a] = find(dsu[a]);
}
bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a==b)return 0;
    dsu[b] = a;
    sz[a]+=b;
    owo(i, 0, 30) {
        cnt[a][i][0]+=cnt[b][i][0];
        cnt[a][i][1]+=cnt[b][i][1];
    }
    return 1;
}
int main() {
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    p2[0] = 1;
    owo(i, 1, mxN) {
        p2[i] = (p2[i-1]*2)%MOD;
    }
    owo(i, 0, n) {
        cin>>val[i];
        dsu[i] = i;
        sz[i] = 1;
        owo(bit, 0, 30) {
            cnt[i][bit][(val[i]>>bit)&1]++;
        }
    }
    iota(ord, ord+n, 0);
    sort(ord, ord+n, [&](int a, int b) {
        return val[a] > val[b];
    });
    int a, b;
    owo(i, 1, n) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    owo(id, 0, n) {
        int i = ord[id];
        done[i] = true;
        memset(sub, 0, sizeof(sub));
        for(int k: adj[i]) {
            k = find(k);
            if(!done[k])continue;
            owo(bit, 0, 30) {
                if(cnt[k][bit][1]) {
                    ll inc = (p2[cnt[k][bit][0]]*p2[cnt[k][bit][1]-1])%MOD;
                    sub[bit][1] = (sub[bit][1] + inc)%MOD;
                    sub[bit][0] = (sub[bit][0] + inc - 1)%MOD;
                }else {
                    sub[bit][0] = (sub[bit][0] + p2[cnt[k][bit][0]] - 1)%MOD;
                    
                }
            }
            merge(i, k);
        }
        owo(bit, 0, 30) {
            int x = (val[i]>>bit)&1;
            ll res = 0;
            if(cnt[i][bit][1]) {
                res = (p2[cnt[i][bit][0]]*p2[cnt[i][bit][1]-1] - x)%MOD;
            }
            ans = (ans + (res-sub[bit][x^1])*p2[bit])%MOD;
        }
    }
    if(ans < 0) ans+=MOD;
    cout<<ans<<"\n";
    return 0;
}
