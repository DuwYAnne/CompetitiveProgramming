#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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
map<int, ll> mp[mxN];
vector<int> adj[mxN];
int d[mxN];
int w[mxN];
int n, m, k;
void dfs(int u=0) {
    for(int v:adj[u]){
        dfs(v);
        if(mp[v].size()>mp[u].size()) {
            swap(mp[v], mp[u]);   
        }
        for(auto p: mp[v]) {
            mp[u][p.first]+=p.second;   
        }
        mp[v].clear();
    }
    if(w[u]!=0) {
        int val = w[u];
        while(1) {
            auto it = mp[u].upper_bound(d[u]);
            if(it==mp[u].end())break;
            if(it->second<val) {
                val-=it->second;
                mp[u].erase(it);
            }else {
                mp[u][it->first]-=val;
                break;
            }
        }
        mp[u][d[u]]+=w[u];
    }
}
vector<int> arr[mxN];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    int a;
    owo(i, 1, n) {
        cin>>a;
        a--;
        adj[a].senpai(i);
    }
    owo(i, 0, m) {
        cin>>a;
        a--;
        cin>>d[a]>>w[a];
    }
    dfs();
    ll ans = 0;
    for(auto it: mp[0]) {
        ans+=it.second;
    }
    cout<<ans<<"\n";
    return 0;
}
