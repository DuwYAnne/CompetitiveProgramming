/*Its easy to see the answer is upperbounded by n + m - 1.
Next, we assume we will do all horizontal slices, and find the minimum vertical slices. 
For some interval [a, b] of vertical slices we have left, we calculate some [l, r], the least segment of horizontal slices we have left at this state.
How to compute this? Just calculate [a-1, b] and [a, b+1] first, then if you can transition from those states, cut as many from their respective[l, r] state.
This works because if some [a, b] is reachable, and the best is [l, r], then no matter what segment you enter [a, b] from, you will end at [l, r]
Additionally, if you could enter with some [l+x, r-y], the best would also be [l+x, r-y]. 
Then as long as the [l, r] segment has size 0, that [a, b] interval is good and we update the answer
*/

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
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
const int mxN = 2002;
int n, m;
ll k;
ll psum[mxN][mxN];
int ans = 0;
bool ok[mxN][mxN];
ll geth(int h, int l, int r) {
    return psum[h+1][r+1] - psum[h+1][l] - psum[h][r+1] + psum[h][l];
}
ll getv(int v, int l, int r) {
    return psum[r+1][v+1] - psum[l][v+1] - psum[r+1][v] + psum[l][v];
}
void calch(int a, int b, int l, int r) {
    if(ok[a][b]) return;
    ok[a][b] = 1;
    while(geth(l, a, b) <= k && l <= r)l++;
    while(geth(r, a, b) <= k && l <= r)r--;
    if(l > r) ans = min(ans, m + a + n - 1 - b);
    else {
        if(getv(a, l, r) <= k)calch(a+1, b, l, r);
        if(getv(b, l, r) <= k)calch(a, b-1, l, r);
    }
    ok[a][b] = 1;
    return;
}
void calcv(int a, int b, int l, int r) {
    if(ok[a][b]) return;
    while(getv(l, a, b) <= k && l <= r)l++;
    while(getv(r, a, b) <= k && l <= r)r--;
    if(l > r) ans = min(ans, m + a + n - 1 - b);
    else {
        if(geth(a, l, r) <= k)calcv(a+1, b, l, r);
        if(geth(b, l, r) <= k)calcv(a, b-1, l, r);
    }
    ok[a][b] = 1;
    return;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>k>>m>>n;
    owo(i, 1, n+1) {
        owo(j, 1, m+1) {
            cin>>psum[i][j];
        }
    }
    owo(i, 1, n+1) {
        owo(j, 1, m+1) {
            psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
            //cout<<i<<" "<<j<<" "<<psum[i][j]<<"\n";
        }
    }
    ans = n+m-1;
    memset(ok, 0, sizeof(ok));
    calch(0, m-1, 0, n-1);
    memset(ok, 0, sizeof(ok));
    calcv(0, n-1, 0, m-1);
    cout<<ans<<"\n";
}
