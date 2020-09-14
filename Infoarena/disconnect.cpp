//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define owo(i,a, b) for(auto i=(a);i<(b); ++i)
#define uwu(i,a, b) for(auto i=(a)-1; i>=(b); --i)
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
const ll MOD = 1000000007;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 100001;
//just random lol
vector<int> adj[mxN];
ttgl inout[mxN];
int par[mxN];
int cnt = 0;
ll sgxor[8*mxN];
ll del[8*mxN];
int n, m;
void push(int i) {
    del[2*i]^=del[i];
    del[2*i+1]^=del[i];
    del[i] = 0;
}
void resolve(int i) {
    sgxor[i] = sgxor[2*i]^del[2*i]^sgxor[2*i+1]^del[2*i+1];
}
void upd(int l, int r, ll ch, int le = 0, int rr = 2*n-1, int i = 1) {
    if(le > r || rr < l) return;
    if(le >= l && rr <= r) {
        del[i]^=ch;
        return;
    }
    int mid = (le + rr) >> 1;
    push(i);
    upd(l, r, ch, le, mid, 2*i);
    upd(l, r, ch, mid+1, rr, 2*i+1);
    resolve(i);
}
ll query(int pos, int le = 0, int rr = 2*n-1, int i = 1) {
    if(le==rr) {
        return sgxor[i]^del[i];
    }
    int mid = (le + rr) >> 1;
    push(i);
    if(pos >= le && pos <= mid) {
        return query(pos, le, mid, 2*i);
    }else {
        return query(pos, mid+1, rr, 2*i+1);
    }
}
void dfs(int u, int p = -1) {
    inout[u].first = cnt++;
    for(int v: adj[u]) {
        if(v^p) {
            par[v] = u;
            dfs(v, u);
        }
    }
    inout[u].second = cnt++;
}
int main() {
    freopen("disconnect.in", "r", stdin);
    freopen("disconnect.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b;
    owo(i, 0, n-1) {
        cin>>a>>b;
        a--; b--;
        adj[a].senpai(b);
        adj[b].senpai(a);
    }
    dfs(0);
    int V = 0;
    int c;
    while(m--) {
        cin>>c>>a>>b;
        a^=V;
        b^=V;
        a--; b--;
        //cout<<a<<" "<<b<<" "<<endl;
        if(c==1) {
            if(a==par[b]) swap(a, b);
            //cout<<a<<" "<<inout[a].first<<" "<<inout[a].second<<endl;
            upd(inout[a].first, inout[a].second, rng());
        }else {
            if(query(inout[a].first)==query(inout[b].first)) {
                cout<<"YES\n";
                V = a+1;
            }else {
                cout<<"NO\n";
                V = b+1;
            }
        }
    }
    return 0;
}
