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
const int mxN = 100005;
ttgl arr[mxN];
int seg[4*mxN];
int segmax[4*mxN];
int del[4*mxN];
int n;
void push(int i) {
    del[2*i]+=del[i];
    del[2*i+1]+=del[i];
    del[i] = 0;
}
void resolve(int i) {
    seg[i] = min(seg[2*i] + del[2*i], seg[2*i+1] + del[2*i+1]);
    segmax[i] = max(segmax[2*i] + del[2*i], segmax[2*i+1] + del[2*i+1]);
}
void upd(int l, int r, int ch, int i=1, int le = 0, int rr = mxN-1) {
    if(l>r)return;
    if(le>r||rr<l) return;
    if(le>=l&&rr<=r) {
        del[i]+=ch;
        return;
    }
    int mid = (le+rr)/2;
    push(i);
    upd(l, r, ch, 2*i, le, mid);
    upd(l, r, ch, 2*i+1, mid+1, rr);
    resolve(i);
    return;
}
int getnum(int pos, int i=1, int le=0, int rr=mxN-1) {
    if(le>pos||rr<pos)return INF;
    if(le==rr&&le==pos) {
        return seg[i]+del[i];
    }
    push(i);
    resolve(i);
    int mid = (le+rr)/2;
    return min(getnum(pos, 2*i, le, mid), getnum(pos, 2*i+1, mid+1, rr));
}
int query(int val, int i=1, int le = 0, int rr=mxN-1) {
    //cout<<val<<" "<<le<<" "<<rr<<" "<<(seg[i]+del[i])<<endl;
    if(i==1&&val>segmax[i]+del[i]) {
        return 0;
    }
    if(le==rr) {
        if(val>segmax[i]+del[i]) return le;
        else return mxN;
    }
    push(i);
    resolve(i);
    int mid = (le+rr)/2;
    if(val>seg[2*i] + del[2*i]) {
        return query(val, 2*i, le, mid);
    }else {
        return query(val, 2*i+1, mid+1, rr);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i].first>>arr[i].second;
        arr[i].first--;
    }
    sort(arr, arr+n);
    //query(0);
    owo(i, 0, n) {
        int start = arr[i].first-arr[i].second+1;
        int smal = getnum(start);
        int r = min(query(smal)-1, arr[i].first);
        int l = query(smal+1);
        //cout<<arr[i].first<<" "<<arr[i].second<<" "<<smal<<" "<<l<<" "<<r<<" "<<start<<"\n";
        upd(l, l+r-start, 1);
        upd(r+1, arr[i].first, 1);
        //cout<<"----------------------\n";
        //owo(i, 0, 6) {
            //cout<<getnum(i)<<" ";
        //}
        //cout<<"\n";
        //query(0);
    }
    ll ans =0;
    owo(i, 0, mxN) {
        int val = getnum(i);
        ans+=1LL*val*(val-1)/2;
    }
    cout<<ans<<"\n";
    return 0;
}
