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
const ll MOD = 998244353;
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
const int mxN = 1<<22;
int two[22];
int ans[mxN];
int arr[mxN];
int n, m, q;
int main() {
    freopen("xortransform.in", "r", stdin);
    freopen("xortransform.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>q;
    two[0] = 1;
    owo(i, 1, 22) {
        two[i] = two[i-1]*2;
    }
    int a;
    owo(i, 0, n) {
        owo(j, 0, m) {
            cin>>a;
            arr[i|j]^=a;
        }
    }
    owo(msk, 0, mxN) {
        ans[msk] = arr[msk];
    }
    owo(i, 0, 22)owo(msk, 0, 1<<22) {
        if(msk&(two[i])) {
            ans[msk]^=ans[msk^(two[i])];
        }
    }
    int prev = 0;
    while(q--) {
        cin>>a;
        prev^=a;
        cout<<(prev=ans[(mxN-1)&prev])<<"\n";
    }
    return 0;
}
