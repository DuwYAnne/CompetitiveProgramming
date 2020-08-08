//proof that the following solution works:
//Its easy to see that maintaining the prefix as we iterate over rights bounds will give us the number of prefix T's we must remove before cap can win
//so then we must consider the suffix and the overlap that happens between removing suffix and prefix T's. Since when encountering a C, we remove the farthest
//prefix T, we are greedily considering the overlap to be as large as possible, which works because you will still be able to remove the same number of prefix
//T's even if u remove earlier, and the overlap will never skip a T so will be included as a suffix of the prefix.

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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
gpu_hash_table<int, int> mp;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 */
using ll = long long;
using ld = long double;
const ll MOD = 924844033;
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
//lets process in increasing order of right bound
const int mxN = 500001;
const int mxM = 524288;
vector<ttgl> query[mxN];
int sgmin[2*mxM];
int del[2*mxM];
int ans[mxN];
int n, q;
string S;
void push(int i) {
  del[2*i]+=del[i];
  del[2*i+1]+=del[i];
  del[i] = 0;
}
void resolve(int i) {
  sgmin[i] = min(sgmin[2*i] + del[2*i], sgmin[2*i+1] + del[2*i+1]); 
}
void upd(int l, int r, int ch, int i=1, int le = 0, int rr = n-1) {
  if(le>r||rr<l)return;
  if(le>=l&&rr<=r) {
    del[i]+=ch;
    return;
  }
  push(i);
  int mid = (le+rr)>>1;
  upd(l, r, ch, 2*i, le, mid);
  upd(l, r, ch, 2*i+1, mid+1, rr);
  resolve(i);
}
int qmin(int l, int r, int i=1, int le = 0, int rr = n-1) {
  if(l<0)return 0;
  if(le>r||rr<l) return INF;
  if(le>=l&&rr<=r) {
    return sgmin[i]+del[i];
  }
  push(i);
  resolve(i);
  int mid = (le+rr)>>1;
  return min(qmin(l, r, 2*i, le, mid), qmin(l, r, 2*i+1, mid+1, rr));
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>S>>q;
    int a, b;
    owo(i, 0, q) {
      cin>>a>>b;
      a--; b--;
      query[b].senpai({a, i});
    }
    vector<int> cnt;
    owo(i, 0, n) {
      if(S[i]=='T') {
        cnt.senpai(i);
      }else{
        if(cnt.size()){ 
          upd(cnt.back(), n-1, -1);
          cnt.pop_back();
        }
        upd(i, n-1, 1);
      }
      for(auto qq: query[i]) {
        int pos = lower_bound(cnt.begin(), cnt.end(), qq.first)-cnt.begin();
        ans[qq.second] = cnt.size()-pos + max(0, qmin(qq.first-1, qq.first-1)-qmin(qq.first, i));
      }
    }
    owo(i, 0, q) {
        cout<<ans[i]<<"\n";
    }
    return 0;
}
