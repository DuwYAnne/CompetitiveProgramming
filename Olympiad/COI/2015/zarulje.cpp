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
ll fact[mxN];
ll ifact[mxN];
int arr[mxN];
int r[mxN];
int l[mxN];
vector<int> rr[mxN];
vector<int> rl[mxN];
ll res[mxN];
ll ans = 1;
int cnt[mxN][2];
int n, q;
ll nCr(int n, int r) {
    if(r > n || r < 0)return 0;
    return ((fact[n] * ifact[r])%MOD * ifact[n-r])%MOD;
}
ll rnCr(int n, int r) {
    if(r > n || r < 0)return 0;
    return ((ifact[n] * fact[r])%MOD * fact[n-r])%MOD;
}
void cl(int i, int del) {
    ans = (ans * rnCr(cnt[i][0] + cnt[i][1], cnt[i][0]))%MOD;
    cnt[i][0]+=del;
    ans = (ans * nCr(cnt[i][0] + cnt[i][1], cnt[i][0]))%MOD;
}
void cr(int i, int del) {
    ans = (ans * rnCr(cnt[i][0] + cnt[i][1], cnt[i][0]))%MOD;
    cnt[i][1]+=del;
    ans = (ans * nCr(cnt[i][0] + cnt[i][1], cnt[i][0]))%MOD;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    fact[0] = 1;
    owo(i, 1, mxN) {
        fact[i] = (fact[i-1]*i)%MOD;
    }
    ifact[mxN-1] = modInv(fact[mxN-1]);
    uwu(i, mxN-1, 0) {
        ifact[i] = (ifact[i+1]*(i+1))%MOD;
    }
    int mn = INF;
    owo(i, 0, n) {
        cin>>arr[i];
        arr[i]--;
        if(i) {
            if(arr[i] <= mn) {
                cnt[arr[i]][1]++;
            }
            mn = min(mn, arr[i]);
        }
    }
    owo(i, 0, n) {
        l[i] = i-1;
        while(l[i]>=0 && arr[l[i]] >= arr[i])l[i] = l[l[i]];
        rl[l[i]].senpai(i);
    }
    uwu(i, n, 0) {
        r[i] = i+1;
        while(r[i]<n && arr[r[i]] >= arr[i])r[i] = r[r[i]];
        rr[r[i]].senpai(i);
    }
    owo(i, 0, mxN) {
        //cout<<cnt[i][0]<<" "<<cnt[i][1]<<"\n";
        ans = (ans * nCr(cnt[i][0] + cnt[i][1], cnt[i][0]))%MOD;
    }
    res[0] = ans;
    owo(i, 1, n) {
        cl(arr[i-1], 1);
        for(int k : rr[i-1]) {
            cl(arr[k], -1);
        }
        cr(arr[i], -1);
        for(int k: rl[i]) {
            cr(arr[k], 1);
        }
        res[i] = ans;
    }
    int a;
    while(q--) {
        cin>>a;
        cout<<res[a-1]<<"\n";
    }
    return 0;
}
