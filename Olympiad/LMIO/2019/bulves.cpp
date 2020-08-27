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
const int mxN = 500001;
ll arr[mxN];
ll c[mxN];
int n;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    priority_queue<ll> pq;
    cin>>n;
    ll k, a, b;
    ll ans = 0;
    owo(i, 1, n+1) {
        cin>>a>>b;
        c[i] = c[i-1] + a - b;
    }
    owo(i, 1, n+1) {
        if(c[i]>c[n]) {
            ans+=c[i]-c[n];
            c[i] = c[n];
        }
        if(c[i]<0) {
            ans-=c[i];
            c[i] = 0;
        }
        pq.push(c[i]);
        k = c[i];
        while(pq.top()>k) {
            ans+=pq.top()-k;
            ll temp = pq.top();
            pq.pop();
            pq.push(k);
            k = temp;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
