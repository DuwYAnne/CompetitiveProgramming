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
const int mxN = 200001;
const int mxM = 262144;
int n;
struct segtree {
    ttgl seg[2*mxM];
    ttgl merge(ttgl a, ttgl b) {
        if(a.first>b.first) return a;
        if(b.first>a.first) return b;
        return {a.first, (a.second+b.second)%MOD};
    }
    void upd(int l, int r, int val, ttgl nxt, int i = 1) {
        //cout<<l<<" "<<r<<" "<<val<<"\n";
        if(l==r) {
            seg[i] = merge(seg[i], nxt);
            return;
        }
        int mid = (l + r)/2;
        if(val <= mid) {
            upd(l, mid, val, nxt, 2*i);
        }else{
        upd(mid+1, r, val, nxt, 2*i+1);
        }
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    }
    ttgl query(int l, int r, int le = 0, int rr = n, int i = 1) {
        if(le>r||rr<l) {
            return {0, 0};
        }
        if(le>=l&&rr<=r) {
            return seg[i];
        }
        int mid = (le + rr)/2;
        return merge(query(l, r, le, mid, 2*i), query(l, r, mid+1, rr, 2*i+1));
    }
}up, down;
int arr[mxN];
int l[mxN], r[mxN], cntl[mxN], cntr[mxN];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    vector<int> o;
    owo(i, 0, n) {
        cin>>arr[i];
        o.push_back(arr[i]);
    }
    sort(o.begin(), o.end());
    o.resize(unique(o.begin(), o.end()) - o.begin());
    owo(i, 0, n) {
        arr[i] = lower_bound(o.begin(), o.end(), arr[i]) - o.begin();
    }
    int mxL = 0;
    uwu(i, n, 0) {
        tie(l[i], cntl[i]) =  down.query(0, arr[i]-1);
        l[i]++;
        if(l[i]==1)cntl[i] = 1;
        tie(r[i], cntr[i]) = up.query(arr[i]+1, n);
        r[i]++;
        if(r[i]==1)cntr[i] = 1;
        //cout<<i<<" "<<l[i]<<" "<<r[i]<<" "<<cntl[i]<<" "<<cntr[i]<<" "<<arr[i]<<"\n";
        down.upd(0, n, arr[i], {l[i], cntl[i]});
        up.upd(0, n, arr[i], {r[i], cntr[i]});
        mxL = max(mxL, l[i] + r[i] - 1);
    }
    ll ans = 0;
    owo(i, 0, n) {
        if(l[i] + r[i] - 1 == mxL) {
            ans = (ans + 1LL*cntl[i]*cntr[i])%MOD;
        }
    }
    ans = (ans*binpow(2, n-mxL))%MOD;
    cout<<mxL<<" "<<ans<<"\n";
    return 0;
}
