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
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 100011;
int n, m, k;
vector<ttgl> adj[2*mxN];
bool flag[2*mxN];
int col[2*mxN];
    ll ans = 0;
int val(int x, int y) {
    if(x==0)return y;
    return m+x-1;
}
set<int> pre;
void solve(int z) {
    bool ok = true;
    ll cnt = 1;
    for(int k: pre) {
        if(flag[k])continue;
        queue<int> Q;
        Q.push(k);
        flag[k] = true;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            //cout<<u<<"\n";
            for(auto v: adj[u]) {
                //cout<<u<<" "<<v.first<<" "<<v.second<<" "<<" "<<col[u]<<" "<<col[v.first]<<"\n";
                if(flag[v.first]) {
                    if(col[v.first]!=col[u]^v.second^z){
                        ok = false;
                        break;
                    }
                    continue;
                }
                if(pre.count(v.first)) {
                    if(col[v.first]!=col[u]^v.second^z) {
                        ok = false;
                        break;
                    }
                }
                flag[v.first] = true;
                col[v.first] = col[u]^v.second^z;
                Q.push(v.first);
            }
        }
    }
    owo(i, 1, n) {
        int k = val(i, 0);
        if(flag[k])continue;
        queue<int> Q;
        Q.push(k);
        flag[k] = true;
        col[k] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto v: adj[u]) {
                if(flag[v.first]) {
                    if(col[v.first]!=col[u]^v.second^z){
                        ok = false;
                        break;
                    }
                    continue;
                }
                flag[v.first] = true;
                col[v.first] = col[u]^v.second^z;
                Q.push(v.first);
            }
        }
        cnt*=2;
        cnt%=1000000000;
    }
    owo(i, 1, m) {
        int k = val(0, i);
        if(flag[k])continue;
        queue<int> Q;
        Q.push(k);
        flag[k] = true;
        col[k] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto v: adj[u]) {
                if(flag[v.first]) {
                    if(col[v.first]!=col[u]^v.second^z){
                        ok = false;
                        break;
                    }
                    continue;
                }
                flag[v.first] = true;
                col[v.first] = col[u]^v.second^z;
                Q.push(v.first);
            }
        }
        cnt*=2;
        cnt%=1000000000;
    }
    owo(i, 1, n) {
        int k = val(i, 0);
        if(pre.count(k))continue;
        col[k] = -1;
    }
    owo(i, 1, m) {
        int k = val(0, i);
        if(pre.count(k))continue;
        col[k] = -1;
    }
    memset(flag, false, sizeof(flag));
    if(ok)ans+=cnt;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    int x, y, c;
    bool one = true;
    bool zero = true;
    memset(col, -1, sizeof(col));
    owo(i, 0, k) {
        cin>>x>>y>>c;
        x--; y--;
        if(x==0&&y==0) {
            if(c) {
                zero = false;
            }else {
                one =false;
            }
            continue;
        }
        if(x==0) {
            col[val(x, y)] = c;
            pre.insert(val(x, y));
            continue;
        }
        if(y==0) {
            col[val(x, y)] = c;
            pre.insert(val(x, y));
            continue;
        }
        c^=((x&1)&&(y&1));
        int aa = val(x, 0);
        int bb = val(0, y);
        //cout<<aa<<" "<<bb<<"\n";
        adj[aa].senpai({bb, c});
        adj[bb].senpai({aa, c});
    }
    //for(auto k: adj[4]) {
        //cout<<k.first<<" "<<k.second<<" \n";
    //}
    if(zero) {
        solve(0);
    }
    if(one) {
        solve(1);
    }
    cout<<(ans%1000000000)<<"\n";
    return 0;
}
