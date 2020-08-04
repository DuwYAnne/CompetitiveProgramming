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
using namespace __gnu_pbds;
gpu_hash_map<int, int> mp;*/
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
const int mxN = 500001;
int n;
int arr[mxN];
int calctime(int x) {
    int res = 0;
    while(x>0) {
        x/=2;
        res+=2;
    }
    return res;
}
multiset<int> ms;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    int ans = 0;
    owo(i, 0, n) {
        cin>>arr[i];
        ans+=calctime(2*arr[i]);
        int num = 0;
        uwu(j, 32, 0) {
            if(arr[i]&(1<<j)) {
                num++;
            }else {
                if(num>0)break;
            }
        }
        ms.insert(num);
    }
    ms.erase(--ms.end());
    while(!ms.empty()) {
        int k = *--ms.end();
        if(k==1) {
            ans-=2;
        }else {
            ms.insert(k-1);
            ms.erase(--ms.end());
        }
        ms.erase(--ms.end());
    }
    cout<<(ans-1)<<"\n";
    return 0;
}
