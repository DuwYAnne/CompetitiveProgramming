#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, gp_hash_table<int, int>> mp;
using ll = long long;
using ld = long double;
const ll MOD = 1000000000;
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
vector<int> adj[mxN];
//map<int, map<int, int>> mp;
ll ans = 0;
ttgl arr[mxN];
int n;
int sum[mxN];
int sz[mxN];
int start[mxN];
void dfs(int u, int p) {
    sum[u]+=sz[u];
    for(int v: adj[u]) {
        if(v^p) {
            dfs(v, u);
            sum[u]+=sum[v];
        }
    }
}
void get(int u, int p) {
    for(int v: adj[u]) {
        if(v^p) {
            get(v, u);
        }
    }
    ans=(ans + 1LL*sum[u]*(sum[0]-sum[u]))%MOD;
}
void solve(){ 
    mp.clear();
    owo(i, 0, mxN) {
        adj[i].clear();
        sz[i] = 0;
        sum[i] = 0;
    }
    sort(arr, arr+n);
    int id =0;
    owo(i, 0, n) {
        int x =arr[i].first;
        int y = arr[i].second;
        if(i>0&&x==arr[i-1].first&&y==arr[i-1].second+1) {
            mp[x][y] = mp[x][y-1];
            sz[mp[x][y]]++;
            if(mp[x-1].find(y)!=mp[x-1].end()&&mp[x-1].find(y-1)==mp[x-1].end()) {
                adj[mp[x][y]].senpai(mp[x-1][y]);
                adj[mp[x-1][y]].senpai(mp[x][y]);
            }
        }else {
            sz[id] = 1;
            mp[x][y] = id++;
            if(mp[x-1].find(y)!=mp[x-1].end()) {
                adj[mp[x][y]].senpai(mp[x-1][y]);
                adj[mp[x-1][y]].senpai(mp[x][y]);
            }
        }
    }
    dfs(0, 0);
    get(0, 0);
}
int DistanceSum(int N, int *X, int *Y) {
    n = N;
    owo(i, 0, n) {
        arr[i] = {X[i], Y[i]};
    }
        int mm = 2*INF;
    int nn = 2*INF;
    owo(i, 0, n) {
        mm = min(mm, arr[i].first);
        nn = min(nn, arr[i].second);
    }
    owo(i, 0, n) {
        arr[i].first-=mm;
        arr[i].second-=nn;
    }
    solve();
    owo(i, 0, n) {
        swap(arr[i].first, arr[i].second);
    }
    solve();
    return (int)ans;
}
/*int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i].first>>arr[i].second;
    }
    int mm = 2*INF;
    int nn = 2*INF;
    owo(i, 0, n) {
        mm = min(mm, arr[i].first);
        nn = min(nn, arr[i].second);
    }
    owo(i, 0, n) {
        arr[i].first-=mm;
        arr[i].second-=nn;
    }
    solve();
    owo(i, 0, n) {
        swap(arr[i].first, arr[i].second);
    }
    solve();
    cout<<ans<<"\n";
    return 0;
}*/
