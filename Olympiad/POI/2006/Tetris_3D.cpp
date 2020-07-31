#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
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
const int mxN = 1001;
const int mxM = 2048;
int n, d, s;
struct segtree {
    int sz;
    vector<int> seg, del;
    segtree() : sz(mxM) {
        seg.resize(mxM); del.resize(mxM);
    }
    void push(int i) {
        del[2*i] = max(del[2*i], del[i]);
        del[2*i+1] = max(del[2*i+1], del[i]);
        seg[2*i] = max(seg[2*i], del[2*i]);
        seg[2*i+1] = max(seg[2*i+1], del[2*i+1]);
        del[i] = 0;
    }
    void resolve(int i) {
        seg[i] = max(seg[2*i], seg[2*i+1]);
    }
    void upd(int ch, int le, int rr, int i=1, int l=0, int r = mxN-1) {
        if(le>r||rr<l) return;
        if(l>=le&&r<=rr) {
            seg[i] = max(seg[i], ch);
            del[i] = max(del[i], ch);
            return;
        }
        push(i);
        int mid = (l+r)/2;
        upd(ch, le, rr, 2*i, l, mid);
        upd(ch, le, rr, 2*i+1, mid+1, r);
        resolve(i);
    }
    int qmax(int le, int rr, int i=1, int l=0, int r = mxN-1){ 
        if(le>r||rr<l)return 0;
        if(l>=le&&r<=rr) {
            return seg[i];
        }
        push(i);
        int mid = (l+r)/2;
        return max(qmax(le, rr, 2*i, l, mid), qmax(le, rr, 2*i+1, mid+1, r));
    }
};
struct seg2 {
    int sz;
    vector<segtree> sgmax, sgo;
    seg2() : sz(mxM) {
        sgmax.resize(mxM); sgo.resize(mxM);
    }
    void upd(int xl, int xr, int yl, int yr, int ch, int i=1, int l=0, int r=mxN-1) {
        if(xl>r||xr<l)return;
        if(l>=xl&&r<=xr) {
            sgmax[i].upd(ch, yl, yr);
            sgo[i].upd(ch, yl, yr);
            return;
        }
        int mid = (l+r)/2;
        upd(xl, xr, yl, yr, ch, 2*i, l, mid);
        upd(xl, xr, yl, yr, ch, 2*i+1, mid+1, r);
        sgmax[i].upd(ch, yl, yr);
    }
    int qmax(int xl, int xr, int yl, int yr, int i=1, int l=0, int r=mxN-1){
        if(xl>r||xr<l)return 0;
        if(l>=xl&&r<=xr) {
            return sgmax[i].qmax(yl, yr);
        }
        int mid = (l+r)/2;
        return max({qmax(xl, xr, yl, yr, 2*i, l, mid), qmax(xl, xr, yl, yr, 2*i+1, mid+1, r), sgo[i].qmax(yl, yr)});
    }
}ans;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>d>>s>>n;
    int q, w, e, r, t;
    while(n--) {
        cin>>q>>w>>e>>r>>t;
        ans.upd(r, r+q-1, t, t+w-1, ans.qmax(r, r+q-1, t, t+w-1) + e);
    }
    cout<<(ans.qmax(0, d, 0, s))<<"\n";
    return 0;
}
