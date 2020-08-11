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
/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
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
//this problem is the same as building a virtual tree of the nodes on an implicit tree
const int mxN = 100001;
const int lgn = 31;
vector<pair<ll, ll>> adj[mxN*lgn];
pair<ll, ll> arr[mxN];
pair<ll, ll> all[mxN];
ll cnt[mxN*lgn];
ll flag[mxN*lgn];
ll depth[mxN*lgn];
int n;
ll ans = INFLL;
vector<pair<ll, ll>> ii;
map<ll, vector<ll>> xval, yval;
int getbit(int a) {
    if(a==0)return 32;
    else return __builtin_ctzll(a);
}
void dfs(int u) {
    cnt[u] = flag[u];
    for(auto v: adj[u]) {
        depth[v.first] = depth[u] + v.second;
        dfs(v.first);
        cnt[u]+=cnt[v.first];
    }
}
void solve(int u, ll tot) {
    ans = min(ans, tot);
    for(auto v: adj[u]) {
        solve(v.first, tot + (n-2*cnt[v.first])*v.second);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    ll a, b;
    ii.senpai({0, 0});
    owo(i, 0, n) {
        cin>>a>>b;
        arr[i] = {a, b};
        while(a!=0||b!=0) {
            //cout<<a<<" "<<b<<"\n";
            ll na = 0;
            ll nb = 0;
            ii.senpai({a, b});
            na = getbit(a);
            nb = getbit(b);
            if(na<nb) {
                a = a-(1LL<<na);
            }else {
                b = b-(1LL<<nb);
            }
        }
    }    
    sort(ii.begin(), ii.end());
    ii.resize(unique(ii.begin(), ii.end()) - ii.begin());
    owo(i, 0, ii.size()) {
        //cout<<ii[i].first<<" "<<ii[i].second<<"\n";
        xval[ii[i].first].senpai(ii[i].second);
        yval[ii[i].second].senpai(ii[i].first);
    }
    owo(i, 0, n) {
        int k = lower_bound(ii.begin(), ii.end(), arr[i])-ii.begin();
        flag[k]++;
    }
    for(auto p: xval) {
        ll mx = 1LL<<getbit(p.first);
        vector<ll> ys = p.second;
        owo(i, 1, ys.size()) {
            ll a = ys[i-1];
            ll b = ys[i];
            if(b-a<mx) {
                int k1 = lower_bound(ii.begin(), ii.end(), make_pair(p.first, a))-ii.begin();
                int k2 = lower_bound(ii.begin(), ii.end(), make_pair(p.first, b))-ii.begin();
                adj[k1].senpai({k2, b-a});
                //cout<<k1<<" "<<k2<<" "<<b<<" "<<a<<"\n";
            }
        }
    }
    for(auto p: yval) {
        ll mx = 1LL<<getbit(p.first);
        vector<ll> xs = p.second;
        owo(i, 1, xs.size()) {
            ll a = xs[i-1];
            ll b = xs[i];
            if(b-a<mx) {
                int k1 = lower_bound(ii.begin(), ii.end(), make_pair(a, p.first))-ii.begin();
                int k2 = lower_bound(ii.begin(), ii.end(), make_pair(b, p.first))-ii.begin();
                adj[k1].senpai({k2, b-a});
                //cout<<k1<<" "<<k2<<" "<<b<<" "<<a<<"\n";
            }
        }
    }
    dfs(0);
    ll fe = 0;
    owo(i, 0, ii.size()) {
        fe+=depth[i]*flag[i];
    }
    //cout<<fe<<"\n";
    solve(0, fe);
    cout<<ans<<"\n";
    return 0;
}
