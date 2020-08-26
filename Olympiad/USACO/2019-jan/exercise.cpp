#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a); i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
using ll = long long;
using ld = long double;
const ll MOD = 998244353;
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 200001;
vector<int> adj[mxN];
vector<int> tree[mxN];
int all[mxN];
ll start[mxN];
ll ed[mxN];
int par[mxN][19];
int depth[mxN];
ll psum[mxN];
vector<array<int, 3>> query;
map<ttgl, int> mp;
int n, m;
void dfs(int u, int p) {
    par[u][0] = p;
    for(int v: tree[u]) {
        if(v!=p) {
            depth[v] = depth[u]+1;
            dfs(v, u);
        }
    }
}
ll ans =0;
int lca(int i, int j) {
    int a = i;
    int b = j;
    uwu(d, 19, 0) {
        if((depth[b]-depth[a])&(1<<d)&&depth[b]>depth[a]) {
            b  = par[b][d];
        }
    }
    uwu(d, 19, 0) {
        if((depth[a]-depth[b])&(1<<d)&&depth[a]>depth[b]) {
            a = par[a][d];
        }
    }
    if(a==b) {
        if(depth[i]<depth[j]) {
            uwu(d, 19, 0) if(depth[par[j][d]]>depth[i])j = par[j][d];
            start[j]++;
            ans-=start[j];
        }else if(depth[j]<depth[i]) {
            uwu(d, 19, 0) if(depth[par[i][d]]>depth[j])i = par[i][d];
            start[i]++;
            ans-=start[i];
        }
        return a;
    }
    uwu(d, 19, 0){
        if(par[a][d]!=par[b][d]) {
            a = par[a][d];
            b = par[b][d];
        }
    }
    //cout<<i<<" "<<j<<" "<<a<<" "<<b<<"\n";
    start[a]++;
    start[b]++;
    ans-=start[a]+start[b];
    if(a>b)swap(a, b);
    mp[{a, b}]++;
    return par[a][0];
}
void solve(int u, int p, ll curr) {
    //cout<<u<<" "<<p<<" "<<curr<<"\n";
    psum[u] = curr;
    for(int v: tree[u]) {
        if(v!=p) {
            solve(v, u, curr+start[v]);
        }
    }
}
int main()
{   
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        tree[a].senpai(b);
        tree[b].senpai(a);
    }
    dfs(0, 0);
    owo(lg, 1, 19) {
        owo(i, 0, n) {
            par[i][lg] = par[par[i][lg-1]][lg-1];
        }
    }
    owo(i, n-1, m) {
        cin>>a>>b;
        a--; b--;
        int node = lca(a, b);
        query.senpai({a, b, node});
    }
    solve(0, 0, 0);
    //cout<<ans<<"\n";
    for(auto p: mp) {
        //cerr<<p.first.first<<endl;
        ll ok = p.second;
        ans-=(ok*(ok-1)/2);
    }
    for(auto p: query) {
        //cout<<psum[p[0]]<<" "<<psum[p[1]]<<" "<<psum[p[2]]<<"\n";
        ans+=psum[p[0]] + psum[p[1]] -2*psum[p[2]];   
    }
    cout<<ans<<"\n";
    return 0;
}
