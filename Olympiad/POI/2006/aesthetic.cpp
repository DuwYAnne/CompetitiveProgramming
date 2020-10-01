//#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
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
const ll MOD = 998244353;
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
//compute dp[i][j] = first i words, j is the first in last line prefix/suffix min over dp and binary searching
const int mxN = 2001;
int arr[mxN];
int psum[mxN];
int dp[mxN][mxN];
int pre[mxN][mxN];
int suf[mxN][mxN];
int m, n;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>m>>n;
    owo(i, 0, n) {
        cin>>arr[i];
        psum[i+1] = psum[i] + arr[i];
    }
    memset(dp, INF, sizeof(dp));
    memset(pre, INF, sizeof(pre));
    memset(suf, INF, sizeof(suf));
    int ans = INF;
    dp[0][0] = 0;
    owo(i, 0, n) {
        owo(j, 0, i+1) {
            int len = psum[i+1] - psum[j] + i-j;
            //cout<<i<<" "<<j<<" "<<len<<"\n";
            if(len > m)continue;
            if(j==0) {
                dp[i][j] = 0;
                continue;
            }
            int r = j;
            int l = 0;
            while(l < r) {
                int mid = (l+r)>>1;
                if(psum[j] - psum[mid] + j-1-mid <= len) {
                    r = mid;
                }else {
                    l = mid + 1;
                }
            }
            //cout<<i<<" "<<j<<" "<<l<<" hier\n";
            if(l) {
                dp[i][j] = min(pre[j-1][l-1] - len, suf[j-1][l] + len);
            }else if(psum[j] - psum[l] + j-1-l<=len){
                dp[i][j] = suf[j-1][0] + len;
            }else {
                dp[i][j] = pre[j-1][0] - len;
            }
        }
        owo(j, 0, i+1) {
            pre[i][j] = dp[i][j] + (psum[i+1] - psum[j] + i-j);
            if(j) {
                pre[i][j] = min(pre[i][j-1], pre[i][j]);
            }
        }
        uwu(j, i+1, 0) {
            suf[i][j] = dp[i][j] - (psum[i+1] - psum[j] + i-j);
            if(j < i) {
                suf[i][j] = min(suf[i][j+1], suf[i][j]);
            }
        }
        owo(j, 0, i+1) {
            if(i==n-1) {
                ans = min(ans, dp[i][j]);
            }
            //cout<<i<<" "<<j<<" "<<dp[i][j]<<" res?\n";
        }
    }
    cout<<ans<<"\n";
    return 0;
}
