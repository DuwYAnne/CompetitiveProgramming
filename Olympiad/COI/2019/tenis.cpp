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
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 998244353;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 100001;
int n, q;
int arr[mxN][3];
int pos[mxN][3];
int val[mxN];
int sgmin[4*mxN];
int del[4*mxN];
void push(int i) {
    del[2*i]+=del[i];
    del[2*i+1]+=del[i];
    del[i] = 0;
}
void pull(int i) {
    sgmin[i] = min(sgmin[2*i] + del[2*i], sgmin[2*i+1] + del[2*i+1]);
}
void upd(int l, int r, int ch, int i = 1, int le = 0, int rr = n-1) {
    if(le > r || rr < l) return;
    if(le >= l && rr <= r) {
        del[i]+=ch;
        return;
    }
    push(i);
    int m = (le + rr) >> 1;
    upd(l, r, ch, 2*i, le, m);
    upd(l, r, ch, 2*i+1, m+1, rr);
    pull(i);
}
int query(int i = 1, int l = 0, int r = n-1) {
    if(l==r)return l;
    push(i);
    pull(i);
    int m = (l + r) >> 1;
    if(sgmin[2*i] + del[2*i]==0) {
        return query(2*i, l, m);
    }
    return query(2*i+1, m+1, r);
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    owo(i, 0, 3)owo(j, 0, n) {
        cin>>arr[j][i];
        arr[j][i]--;
        val[arr[j][i]] = max(val[arr[j][i]], j);
        pos[arr[j][i]][i] = j;
    }
    owo(i, 0, n) {
        upd(i, i, i+1);
        upd(val[i], n-1, -1);
    }
    int a, b, c, d;
    while(q--) {
        cin>>a;
        if(a==1) {
            cin>>b;
            b--;
            cout<<(val[b]<=query() ? "DA\n" : "NE\n");
        }else {
            cin>>b>>c>>d;
            b--; c--; d--;
            upd(val[c], n-1, 1);
            upd(val[d], n-1, 1);
            swap(pos[c][b], pos[d][b]);
            val[c] = 0; val[d] = 0;
            owo(k, 0, 3) {
                val[c] = max(val[c], pos[c][k]);
                val[d] = max(val[d], pos[d][k]);
            }
            upd(val[c], n-1, -1);
            upd(val[d], n-1, -1);
        }
    }
    return 0;
}
