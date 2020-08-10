//#pragma GCC target ("avx2")
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
const int mxN = 2001;
ll dp[mxN][mxN];
string s;
int st, ed;
int n;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>s>>st>>ed;
    n = s.size();
    int edd = 0;
    int stt = 0;
    dp[0][0]=  1;
    owo(i, 1, n+1) owo(j, 1, i+1){
        if(i==st) {
            if(s[i-1]!='L') {//add new comp
                dp[i][j]+=dp[i-1][j-1];
            }
            if(s[i-1]!='R') {//add to old comp
                dp[i][j]+=dp[i-1][j];
            }
            stt = 1;
        }else if(i==ed) {
            //both directions always work
            dp[i][j]+=dp[i-1][j] + dp[i-1][j-1];
            edd = 1;
        }else {
            //open comp
            if(s[i-1]!='L') {
                dp[i][j]+=(max(0, j-stt-edd) * dp[i-1][j-1]) + (j-edd)*dp[i-1][j];
            }
            //close comp
            if(s[i-1]!='R') {
                dp[i][j]+=(j * dp[i-1][j+1]) + (j-stt)*dp[i-1][j];
            }
        }
        dp[i][j]%=MOD;
        //cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
    }
    cout<<dp[n][1]<<"\n";
    return 0;
}
