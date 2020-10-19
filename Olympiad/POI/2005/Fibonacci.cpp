//#pragma GCC target ("avx2")
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
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 1000021;
short a[mxN];
short b[mxN];
short res[mxN];
int s, t;
void split(int i) {
    if(i-2>=0)res[i-2]++;
    res[i+1]++;
    res[i]-=2;
    if(res[i+1]>=2) {
        split(i+1);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>s;
    owo(i, 1, s+1) {
        cin>>a[i];
    }
    cin>>t;
    owo(i, 1, t+1) {
        cin>>b[i];
    }
    int n = max(s, t);
    uwu(i, n+1, 0) {
        res[i] += a[i] + b[i];
        if(res[i] && res[i+1]) {
            res[i]--;
            res[i+1]--;
            res[i+2]++;
        }
        if(res[i] >= 2) {
            split(i);
        }
    }
    if(res[0] && res[1]==0) {
        res[1] = 1;
        res[0] = 0;
    }
    uwu(i, mxN, 0) {
        int curr = i;
        while(curr < mxN && res[curr] && res[curr-1]) {
            res[curr+1]++;
            res[curr] = 0;
            res[curr-1] = 0;
            curr+=2;
        }
    }
    int mxsz = 0;
    owo(i, 0, mxN) {
        if(res[i])mxsz = i;
    }
    cout<<mxsz<<" ";
    owo(i, 1, mxsz+1) {
        cout<<res[i]<<" ";
    }
    return 0;
}
