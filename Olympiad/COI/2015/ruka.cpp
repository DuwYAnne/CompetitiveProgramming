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
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 300001;
int n, m;
//maintain the cursor positon and multiple fenwick trees
struct BIT{ 
    int bit[2*mxN];
    void add(int p, int x) {
        p += mxN;
        while(p < 2*mxN) {
            bit[p] += x;
            p += p&-p;
        }
    }
    void upd(int l, int r, int x) {
        if(l > r) swap(l, r);
        add(l, x);
        add(r + 1, -x);
    }
    int sum(int p) {
        int res = 0;
        p += mxN;
        while(p) {
            res += bit[p];
            p -= p&-p;
        }
        return res;
    }
};
BIT f1[2], f2[2];
int curr[2];
int arr[mxN][2];
int pos[2];
int del[2];
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    pos[0] = 1;
    pos[1] = 1;
    owo(i, 0, n) {
        cin>>arr[i][0]>>arr[i][1];
        if(i) {
            owo(j, 0, 2) {
                f2[j].upd(pos[j], pos[j] + arr[i][j], 1);
                pos[j] += arr[i][j];
            }
        }else {
            owo(j, 0, 2) {
                f1[j].upd(pos[j], pos[j] + arr[i][j], 1);
                pos[j] += arr[i][j];
            }
        }
    }
    cin>>m;
    char z;
    int a, b;
    pos[0] = 1;
    pos[1] = 1;
    int T = 0;
    owo(i, 0, m) {
        cin>>z;
        //cout<<f1[0].sum(0)<<" "<<f1[1].sum(0)<<" "<<f2[0].sum(del[0])<<" "<<f2[1].sum(del[1])<<"\n";
        if(z=='Q') {
            cout<<(f1[0].sum(0) + f1[1].sum(0) + f2[0].sum(del[0]) + f2[1].sum(del[1]))<<"\n";
        }
        if(z=='B') {
            if(T) {
                owo(j, 0, 2) {
                    f1[j].upd(pos[j], pos[j] + arr[T][j], -1);
                    f2[j].upd(pos[j] + del[j], pos[j] + arr[T][j] + del[j], 1);
                    pos[j] -= arr[T-1][j];
                }
                T--;
            }
        }
        if(z=='F') {
            if(T < n-1) {
                T++;
                owo(j, 0, 2) {
                    pos[j] += arr[T-1][j];
                    f1[j].upd(pos[j], pos[j] + arr[T][j], 1);
                    f2[j].upd(pos[j] + del[j], pos[j] + arr[T][j] + del[j], -1);
                }
            }
        }
        if(z=='C') {
            cin>>a>>b;
            del[0] += arr[T][0] - a;
            f1[0].upd(pos[0], pos[0] + arr[T][0], -1);
            f1[0].upd(pos[0], pos[0] + a, 1);
            del[1] += arr[T][1] - b;
            f1[1].upd(pos[1], pos[1] + arr[T][1], -1);
            f1[1].upd(pos[1], pos[1] + b, 1);
            arr[T][0] = a;
            arr[T][1] = b;
        }
    }
    return 0;
}
