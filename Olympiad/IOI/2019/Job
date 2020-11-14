#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define owo(i,a, b) for(auto i=(a);i<(b); ++i)
#define uwu(i,a, b) for(auto i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 200001;
vector<int> adj[mxN];
int p[mxN];
int n;
int dsu[mxN];
bool done[mxN];
bool cmp(array<ll, 3> a, array<ll, 3> b) {
    if(a[0]*b[1]==a[1]*b[0]) {
        return a[2] < b[2];
    }
    return a[0]*b[1] > a[1]*b[0];
}
int find(int a) {
    return a==dsu[a] ? a : dsu[a] = find(dsu[a]);
}
bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a==b)return false;
    dsu[b] = a;
    return true;
}
ll scheduling_cost(vector<int> par, vector<int> u, vector<int> d) {
    n = par.size();
    iota(dsu, dsu+n, 0);
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, decltype(&cmp)> pq(cmp);
    owo(i, 0, n) {
        pq.push({d[i], u[i], i});
    }
    ll res = 0;
    ll curr = 0;
    while(!pq.empty()) {
        auto[t, cst, id] = pq.top();
        pq.pop();
        //cout<<t<<" "<<cst<<" "<<id<<endl;
        if(tie(t, cst)!=tie(d[id], u[id]) || done[id])continue;
        done[id] = true;
        if(par[id]==-1 || done[find(par[id])]) {
            curr+=t;
            res+=cst*curr;
            continue;
        }
        int nxt = find(par[id]);
        res-=t*u[nxt];
        u[nxt]+=cst;
        d[nxt]+=t;
        merge(nxt, id);
        pq.push({d[nxt], u[nxt], nxt});
    }
    return res;
}
