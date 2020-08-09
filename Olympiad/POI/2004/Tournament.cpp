//#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 
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
//consider that some person cannot win if and only if every winner always beats them
//count edges
const int mxN = 100001;
int n;
int arr[mxN];
vector<int> adj[mxN];
vector<int> toposort;
int cnt[mxN];
bool flag[mxN];
void dfs(int u) {
    flag[u] = true;
    for(int v: adj[u]) {
        if(!flag[v])dfs(v);
    }
    toposort.senpai(u);
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    int a, b;
    owo(i, 0, n) {
        cin>>b;
        while(b--) {
            cin>>a;
            a--;
            adj[i].senpai(a);
        }
    }
    owo(i, 0, n) {
        if(!flag[i]) dfs(i);
    }
    memset(flag, 0, sizeof(flag));
    vector<int> ans;
    ll edges = 0;
    reverse(toposort.begin(), toposort.end());
    for(int p: toposort) {
        ans.senpai(p);
        edges-=cnt[p];
        for(int v: adj[p]) {
            if(!flag[v]) {
                cnt[v]++;
                edges++;
            }
        }
        flag[p] = true;
        if(edges>=1LL*(ans.size())*((ll)n-(ll)ans.size())) break;
    }
    sort(ans.begin(), ans.end());
    cout<<ans.size()<<" ";
    for(auto u: ans) {
        cout<<(u+1)<<" ";
    }
    return 0;
}
