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
const int mxN = 513;
int n;
int dp[mxN][mxN];//dp[i][j] = number j at position i
int arr[mxN][mxN];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    n = (1<<n);
    owo(i, 0, n) {
        owo(j, 0, n) {
            cin>>arr[i][j];
        }
    }
    memset(dp, INF, sizeof(dp));
    owo(i, 0, n) {
        dp[i][0] = 0;
    }
    owo(i, 1, n) {
        int level = i&-i;
        owo(j, 0, n) {
            int k = 0;
            if(j&level) {//right half
                k = (j-level)&~(level-1);
            }else {//left half
                k = (j+level)&~(level-1);
            }
            owo(b, k, k+level) {
                dp[b][i] = min(dp[b][i], dp[j][i-1] + arr[j][b]);
                //cout<<b<<" "<<j<<" "<<i<<" "<<dp[b][i]<<"\n";
            }
        }
    }
    int ans = INF;
    owo(i, 0, n) {
        ans = min(ans, dp[i][n-1]);
    }
    cout<<ans<<"\n";
    return 0;
}
