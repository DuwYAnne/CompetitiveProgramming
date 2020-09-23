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
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
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
const int mxN = 10001;
float dp[mxN][201];
int prv[mxN][201];
float lgn[mxN];
bool prime[mxN];
vector<int> primes;
int d, n;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>d;
    owo(i, 1, mxN) {
        lgn[i] = log(i);
    }
    memset(prime, true, sizeof(prime));
    prime[0] = false;
    prime[1] = false;
    owo(i, 2, mxN) {
        if(prime[i]) {
            primes.senpai(i);
            for(int j = 2*i; j < mxN; j += i) {
                prime[j] = false;
            }
        }
    }
    while(d--) {
        vector<int> res;
        int cnt = 0;
        cin>>n;
        int tot = n;
        for(int i = 1; primes[i-1] <= n && i < 200; ++i) {
            uwu(j, n+1, 1) {
                dp[j][i] = dp[j][i-1];
                prv[j][i] = 0;
                cnt = max(cnt, i);
                int pp = 1;
                while(pp <= j) {
                    if(dp[j - pp][i - 1] + lgn[pp] > dp[j][i] + eps) {
                        dp[j][i] = dp[j - pp][i - 1] + lgn[pp];
                        prv[j][i] = pp;
                    }
                    pp = pp * primes[i-1];
                }
            }
        }
        while(n && cnt) {
            res.push_back(prv[n][cnt]);
            n-=prv[n][cnt--];
        }
        sort(res.begin(), res.end());
        for(int k: res) {
            tot-=k;
        }
        int curr = 1;
        //cout<<tot<<"\n";
        owo(i, 0, tot) {
            cout<<(curr++)<<" ";
        }
        for(int k: res) {
            if(k==0)continue;
            owo(i, 0, k-1) {
                cout<<(++curr)<<" ";
            }
            cout<<(++curr-k)<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
