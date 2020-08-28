//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
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
const int mxN = 1000001;
//f(i) = time to write ith character;
string s;
int n, k;
double f[mxN];
array<double, 3> p[27];
double ans = 0;
int main() {
    freopen("sms.in", "r", stdin);
    freopen("sms.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    cin>>s;
    owo(i, 0, k) {
        cin>>p[i][0]>>p[i][1]>>p[i][2];
    }
    owo(i, 0, n) {
        if(i) {
            f[i] = (1.0 + p[s[i]-'a'][1] + p[s[i]-'a'][2]*f[i-1]);
        }else {
            f[i] = (1.0 + p[s[i]-'a'][1]);
        }
        f[i] /= p[s[i]-'a'][0];
        ans+=f[i];
    }
    cout<<setprecision(12)<<ans<<"\n";
    return 0;
}
