#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> mp;*/
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 100001;
int n;
int bcount[1<<20];
void precomp() {
    owo(i, 0, 1<<20) {
        bcount[i] = __builtin_popcount(i);
    }
}
int arr[mxN];
int k[mxN];
ttgl dp[1<<10][1<<10][11];
int par[mxN];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i];
    }
    owo(i, 0, n) {
        cin>>k[i];
    }
    owo(i, 0, 1<<10)owo(j, 0, 1<<10)owo(b, 0, 11) {
        dp[i][j][b] = {0, -1};
    }
    precomp();
    ttgl ans = {0, -1};
    owo(i, 0, n) {
        ttgl curr = {-1, 0};
        int sh = arr[i]>>10;
        int fh = arr[i]&((1<<10)-1);
        owo(j, 0, 1<<10) {
            int num = bcount[j&arr[i]];
            int req = k[i]-num;
            if(req<0||req>10) {
                curr = max(curr, {0, -1});
            }else {
                curr = max(curr, dp[j][sh][req]);
            }
        }
        owo(j, 0, 1<<10) {
            if(dp[fh][j][bcount[j&sh]].first<curr.first+1) {
                dp[fh][j][bcount[j&sh]] = {curr.first+1, i};
                par[i] = curr.second;
                if(ans.first<curr.first+1) {
                    ans.first = curr.first+1;
                    ans.second = i;
                }
            }
        }
    }
    vector<int> res;
    while(ans.second!=-1) {
        res.senpai(ans.second+1);
        ans.second = par[ans.second];
    }
    reverse(res.begin(), res.end());
    cout<<ans.first<<'\n';
    for(int p: res) {
        cout<<p<<" ";
    }
    return 0;
}
