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
//very annoying problem
const int mxN = 300001;
const int mxM = 524288;
int n, q;
struct segtree {
    ll sgmax[2*mxM];
    ll sgmin[2*mxM];
    ll del[2*mxM];
    void push(int i) {
        del[2*i] += del[i];
        del[2*i+1] += del[i];
        del[i] = 0;
    }
    void resolve(int i) {
        sgmax[i] = max(sgmax[2*i] + del[2*i], sgmax[2*i+1] + del[2*i+1]);
        sgmin[i] = min(sgmin[2*i] + del[2*i], sgmin[2*i+1] + del[2*i+1]);
    }
    void upd(int l, int r, ll ch, int le = 0, int rr = n-1, int i = 1) {
        if(le>r||rr<l)return;
        if(le>=l&&rr<=r) {
            del[i]+=ch;
            return;
        }
        push(i);
        int mid = (le + rr) >> 1;
        upd(l, r, ch, le, mid, 2*i);
        upd(l, r, ch, mid+1, rr, 2*i+1);
        resolve(i);
    }
    //binsearch for first index x such that x has less than val points
    int lowerbound1(ll val, int le = 0, int rr = n-1, int i = 1) {
        if(sgmin[i] + del[i]>=val)return n;
        if(le==rr)return le;
        push(i);
        resolve(i);
        int mid = (le + rr) >> 1;
        if(sgmin[2*i] + del[2*i]<val) {
            return lowerbound1(val, le, mid, 2*i);
        }else {
            return lowerbound1(val, mid+1, rr, 2*i+1);
        }
    }
    int lowerbound2(ll val, int le = 0, int rr = n-1, int i = 1) {
        if(sgmin[i] + del[i]>val)return n;
        if(le==rr)return le;
        push(i);
        resolve(i);
        int mid = (le + rr) >> 1;
        if(sgmin[2*i] + del[2*i]<=val) {
            return lowerbound2(val, le, mid, 2*i);
        }else {
            return lowerbound2(val, mid+1, rr, 2*i+1);
        }
    }
    ll qmax(int l, int r, int le = 0, int rr = n-1, int i = 1) {
        if(le>r||rr<l) return 0;
        if(le>=l&&rr<=r) {
            return sgmax[i] + del[i];
        }
        push(i);
        resolve(i);
        int mid = (le + rr) >> 1;
        return max(qmax(l, r, le, mid, 2*i), qmax(l, r, mid+1, rr, 2*i+1));
    }
    ll qmin(int l, int r, int le = 0, int rr = n-1, int i = 1) {
        if(le>r||rr<l) return INFLL;
        if(le>=l&&rr<=r) {
            return sgmin[i] + del[i];
        }
        push(i);
        resolve(i);
        int mid = (le + rr) >> 1;
        return min(qmin(l, r, le, mid, 2*i), qmin(l, r, mid+1, rr, 2*i+1));
    }
}a, b;
int arr[mxN];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    owo(i, 0, n) {
        cin>>arr[i];
    }
    int curr = n-1;
    sort(arr, arr+n);
    reverse(arr, arr+n);
    owo(i, 0, n) {
        a.upd(i, i, arr[i]);
        b.upd(i, i, arr[i] + i + 1);
    }
    char z;
    ll val, add;
    while(q--) {
        cin>>z;
        if(z=='Z') {
            while(curr) {
                //cout<<a.qmax(curr, curr)<<" "<<b.qmax(0, curr-1)<<"\n";
                if(a.qmax(curr, curr) + n < b.qmax(0, curr - 1))curr--;
                else {
                    break;
                }
            }
            cout<<(curr+1)<<"\n";
        }else if(z=='B') {
            cin>>val>>add;
            int lst = a.lowerbound1(val);
            //cout<<lst<<" "<<add<<"\n";
            if(lst) {
                a.upd(0, lst-1, add);
                b.upd(0, lst-1, add);
            }
        }else {
            cin>>val>>add;
            int lst = a.lowerbound2(val);
            if(lst<n) {
                a.upd(lst, n-1, -add);
                b.upd(lst, n-1, -add);
            }
        }
    }
    return 0;
}
