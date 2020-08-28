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
const int mxN = 100001;
int n, m;
vector<ttgl> adj[mxN];
vector<int> eulerWalk(int nedges, int src=0) {
  vector<int> D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = adj[x].size();
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = adj[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}
  }
	for (int x : D) if (x < 0 || (int)ret.size() != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}
vector<int> odd;
int cnt = 0;
int main() {
    freopen("ratway.in", "r", stdin);
    freopen("ratway.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b;
    owo(i, 0, m) {
        cin>>a>>b;
        a--; b--;
        //cout<<a<<" "<<b<<"\n";
        adj[a].senpai({b, cnt});
        adj[b].senpai({a, cnt++});
    }
    owo(i, 0, n) {
        if((int)adj[i].size()&1) {
          odd.senpai(i);
        }
    }
    for(int i=0; i < odd.size(); i+=2) {
        //cout<<odd[i]<<" "<<odd[i+1]<<"\n";
        adj[odd[i]].senpai({odd[i+1], cnt});
        adj[odd[i+1]].senpai({odd[i], cnt++});
    }
    if(cnt&1) {
        //cout<<"0 0\n";
        adj[0].senpai({0, cnt});
        adj[0].senpai({0, cnt++});
    }
    vector<int> cycle = eulerWalk(cnt);
    vector<ttgl> ans;
    owo(i, 0, cycle.size()-1) {
      //cout<<cycle[i]<<" - >";
        if((i&1)==0) {
            ans.senpai({cycle[i], cycle[(i+1)%(int)cycle.size()]});
        }else{
            ans.senpai({cycle[(i+1)%(int)cycle.size()], cycle[i]});
        }
    }
    //cout<<"\n";
    cout<<ans.size()<<"\n";
    for(auto k: ans) {
      cout<<(k.first+1)<<" "<<(k.second+1)<<"\n";
    }
    return 0;
}
