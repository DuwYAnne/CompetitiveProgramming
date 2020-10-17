//#pragma GCC target ("avx2")
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
//do a really dumb dp with pruning
const int mxN = 1<<20;
int dp[mxN][10];
int dpprv[mxN][2];
int arr[mxN/2];
int n, d;
void add(int &a, int &b) {
    a = (a + b)%MOD;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>d;
    owo(i, 0, n) {
        cin>>arr[i];
    }
    sort(arr, arr + n);
    dp[0][0] = 1;
    owo(i, 0, n) {
        int hibit = 0;
        owo(j, 0, 20) {
            if(arr[i] & (1<<j))hibit = j;
        }
        owo(j, 0, d) {
            owo(k, 0, 1<<(hibit+1)) {
                if((k^arr[i]) < k) {
                    swap(dp[k^arr[i]][j], dp[k][j]);
                }
            }
        }
        owo(k, 0, 1<<(hibit+1)) {
            dpprv[k][1] = dp[k][0];
        }
        owo(j, 0, d) {
            owo(k, 0, 1<<(hibit+1)) {
                dpprv[k][0] = dpprv[k][1];
                dpprv[k][1] = dp[k][(j+1)%d];
            }
            owo(k, 0, 1<<(hibit+1)) {
                add(dp[k^arr[i]][(j+1)%d], dpprv[k][0]);
            }
        }
    }
    if(n%d==0) {
        dp[0][0] = (dp[0][0] - 1 + MOD)%MOD;
    }
    cout<<dp[0][0]<<"\n";
    return 0;
}
