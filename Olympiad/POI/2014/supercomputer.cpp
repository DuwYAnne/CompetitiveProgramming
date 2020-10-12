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
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
//answer for some k = max(0<=i<=n i + ceil((num_nodes_depth >= i)/k))
//if we multiply by k, we have some function i*k + num_nodes_depth>=i
//maintain by some stack and convex hull
const int mxN = 1000001;
int par[mxN];
int depth[mxN];
int numd[mxN];
int qry[mxN];
int ans[mxN];
int n, q;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    int mxd = 0;
    owo(i, 0, q) {
        cin>>qry[i];
    }
    owo(i, 1, n) {
        cin>>par[i];
        par[i]--;
        depth[i] = depth[par[i]]+1;
        mxd = max(mxd, depth[i]);
        numd[depth[i]]++;
    }
    uwu(i, n, 0) {
        numd[i]+=numd[i+1];
    }
    vector<array<int, 3>> stk;
    owo(i, 0, mxd+1) {
        array<int, 3> nxt = {i, numd[i], 0};
        while(!stk.empty()) {
            auto p = stk.back();
            int overtake = (p[1] - nxt[1] + nxt[0] - p[0] - 1)/(nxt[0] - p[0]);
            //cout<<overtake<<"\n";
            if(overtake <= p[2])stk.pop_back();
            else {
                nxt[2] = overtake;
                break;
            }
        }
        //cout<<nxt[0]<<" "<<nxt[1]<<" "<<nxt[2]<<"\n";
        stk.senpai(nxt);
    }
    //ayaya;

    int curr = 0;
    owo(i, 1, mxN) {
        while(curr + 1 < stk.size() && stk[curr+1][2]==i)curr++;
        ans[i] = stk[curr][0] + (stk[curr][1] + i - 1)/i;
    }
    owo(i, 0, q) {
        cout<<ans[qry[i]]<<" ";
    }
    return 0;
}
