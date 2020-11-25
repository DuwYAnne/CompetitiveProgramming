/*
First consider that the set of what we choose to remove is enough to decide. Then do dp, but we assume that we leave at least one 1 and one 0
This allows us to delete 1's and 0's with no reprecussions because we can append it to the 1/0 we didn't delete and the answer is the same.
Then do casework assuming we get rid of all 1's or 0's and we are done.
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
const int mxN = 5000;
//dp[i][j][k][b] = ith char, j 2's required, last char is k, b flag, then do dumb casework
int n;
int dp[2*mxN + 1][3][4];
int dp_prv[2*mxN + 1][3][4];
int arr[mxN];
bool has[3];
bool d2;
int check(int a) {
    d2 = 0;
    vector<int> b;
    owo(i, 0, n) {
        if(arr[i]!=a) {
            b.senpai(arr[i]);
        }
    }
    d2|=(b[0]==2 || b.back()==2);
    owo(i, 1, b.size()) {
        d2|=(b[i]==2 && b[i-1]==2);
    }
    return count(arr, arr+n, a) + 1 - d2;
}
int solve() {
    cin>>n;
    has[0] = has[1] = has[2] = false;
    d2 = false;
    owo(i, 0, n) {
        cin>>arr[i];
        has[arr[i]] = true;
        if(i && arr[i]==2 && arr[i-1]==2)d2 = true;
    }
    if((!has[0]) || (!has[1])) {
        return 0;
    }
    if((!has[2]) && has[0] && has[1]) {
        return -1;
    }
    int ans = min(check(1), check(0));
    owo(i, mxN - n, mxN + n + 1) owo(j, 0, 3) owo(k, 0, 4) {
        dp[i][j][k] = INF;
    }
    if(arr[0]==0) {
        //take
        dp[5000][2][0] = 1;
        //dont 
        dp[5000][0][1] = 0;
    }else if(arr[0]==1) {
        dp[5000][2][0] = 1;
        dp[5000][1][2] = 0;
    }else {
        dp[4999][2][0] = 1;
        dp[5000][2][0] = 0;
    }
    owo(i, 1, n) {
        owo(i, mxN - n, mxN + n + 1) owo(j, 0, 3) owo(k, 0, 4) {
            dp_prv[i][j][k] = dp[i][j][k];
        }
        owo(i, mxN - n, mxN + n + 1) owo(j, 0, 3) owo(k, 0, 4) {
            dp[i][j][k] = INF;
        }
        owo(j, mxN - n, mxN + n + 1) {
            owo(k, 0, 3) {
                owo(b, 0, 4) {
                    if(dp_prv[j][k][b]==INF)continue;
                    int x = dp_prv[j][k][b];
                    if(arr[i]==0) {
                        //take
                        dp[j][k][b] = min(dp[j][k][b], x+1);
                        if(k==1) {
                            dp[j+1][0][b|1] = min(dp[j+1][0][b|1], x);
                        }else {
                            dp[j][0][b|1] = min(dp[j][0][b|1], x);
                        }
                    }else if(arr[i]==1) {
                        dp[j][k][b] = min(dp[j][k][b], x+1);
                        if(k==0) {
                            dp[j+1][1][b|2] = min(dp[j+1][1][b|2], x);
                        }else {
                            dp[j][1][b|2] = min(dp[j][1][b|2], x);
                        }
                    }else {
                        dp[j-1][k][b] = min(dp[j-1][k][b], x+1);
                        dp[j][2][b] = min(dp[j][2][b], x);
                    }
                }
            }
        }
    }
    owo(i, mxN - n, 5001) {
        owo(j, 0, 3) {
            ans = min(ans, dp[i][j][3]);
        }
    }
    return ans;
}

int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--) {
        cout<<solve()<<"\n";
    }
    return 0;
}
