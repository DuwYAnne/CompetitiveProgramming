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
const int mxN = 100005;
int n;
ttgl arr[mxN];
int BIT[mxN];
int pos[mxN];
int sum(int p) {
  p++;
  int res =0;
  while(p>0) {
    res+=BIT[p];
    p-=p&(-p);
  }
  return res;
}
void add(int p, int val) {
  p++;
  while(p<=n) {
    BIT[p]+=val;
    p+=p&(-p);
  }
}
int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    int ans = 0;
    cin>>n;
    owo(i, 0, n) {
      cin>>arr[i].first;
      arr[i].second = i;
    }
    sort(arr, arr+n);
    owo(i, 1, n) {
      add(arr[i-1].second, 1);
      int num = sum(i-1);
      ans = max(ans, (i-num));
    }
    cout<<(ans==0 ? 1 : ans)<<"\n";
    return 0;
}
