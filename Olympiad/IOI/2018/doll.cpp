#include "doll.h"
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
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 1<<19;
int n, m;
int temp[mxN];
int idx[mxN];
void create_circuit(int M, vector<int> a) {
    m = M;
    a.senpai(0);
    n = a.size();
    int k = 1;
    while(k < n) {
        k<<=1;
    }
    owo(i, 0, k) {
        temp[i + k]=mxN;
    }
    int tt = 0;
    owo(i, 0, k) {
        idx[i] = idx[i>>1];
        if(i&1) {
            idx[i]|=k;
        }
        idx[i]>>=1;
        if(idx[i] > k-n-1)  temp[idx[i] + k] = a[tt++];
    }
    vector<int> x, y;
    int cnt = 0;
    for(int i=k; --i;) {
        int left = i<<1;
        int right = i<<1|1;
        if(temp[left]^temp[right]) {
            temp[i] = --cnt;
            x.senpai(temp[left]);
            y.senpai(temp[right]);
        }else {
            temp[i] = temp[left];
        }
    }
    owo(i, 0, -cnt) {
        if(x[i]==mxN) {
            x[i] = temp[1];
        }
        if(y[i]==mxN) {
            y[i] = temp[1];
        }
    }
    vector<int> c(m+1, temp[1]);
    answer(c, x, y);
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    return 0;
}
