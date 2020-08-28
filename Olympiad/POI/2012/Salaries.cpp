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
vector<int> unused;
vector<ttgl> re;
int par[mxN];
vector<int> G[mxN];
vector<int> chil[mxN];
bool flag[mxN];
bool bd[mxN];
int ans[mxN];
int ed[mxN];
int n;
void dfs(int u, int tp) {
    int num = 0;
    if(u!=tp) {
      chil[tp].senpai(u);
    }
    for(int v: G[u]) {
      if(ans[v])continue;
      num++;
    }
    if(num>1)ed[tp] = min(ed[tp], (int)chil[tp].size());
    for(int v: G[u]) {
      if(ans[v])continue;
      dfs(v, tp);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    memset(flag, false, sizeof(flag));
    int a;
    int rt = 0;
    owo(i, 0, n) {
        cin>>par[i]>>ans[i];
        par[i]--;
        flag[ans[i]] = true;
        if(i==par[i]) {
            rt = i;
            ans[i] = n;
            flag[n] = true;
        }else {
            G[par[i]].senpai(i);
        }
    }
    int cnt = 0;
    owo(i, 1, n+1) {
        if(!flag[i]) unused.senpai(i);
    }
    owo(i, 0, n) {
        if(ans[i]) {
            ed[i] = n+1;
            dfs(i, i);  
            //cout<<i<<" "<<ans[i]<<" "<<ed[i]<<"\n";
            re.senpai({ans[i], i});
        }
    }
    int left = 0;
    int right = 0;
    cnt = 0;
    sort(re.begin(), re.end());
    for(auto k: re) {
        int u = k.second;
        int num = k.first;
        if(chil[u].size()==0)continue;
        left = right;
        while(right<unused.size()&&unused[right]<num&&right-left<chil[u].size())right++;
        if(right==unused.size()||unused[right]>num) {
            int l = 0;
            int r = 0;
            for(r = right-1, l = 0; r >= left && l < ed[u]; r--, l++) {
                ans[chil[u][l]] = unused[r];
            }
            while(cnt < unused.size() && unused[cnt] < num)cnt++;
        }else {
            while(cnt < unused.size() && unused[cnt] < num) {
                bd[unused[cnt]] = 1;
                cnt++;
            }
        }
    }
    owo(i, 0, n) {
        cout<<(bd[ans[i]] ? 0 : ans[i])<<"\n";
    }
    return 0;
}
