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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 
using ll = long long;
using ld = long double;
const ll MOD = 998244353;
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
//consider that some person cannot win if and only if every winner always beats them
//count edges
const int mxN = 201;
bool adm[mxN][mxN];
int n;
vector<int> solve(vector<int> a) {
    if(a.size()<=2) {
        return {a[0]};
    }
    for(int p: a) {
        int cnt = 0;
        owo(i, 0, n) {
            if(adm[p][i])cnt++;
        }
        if(cnt&1) {
            vector<int> nxt;
            for(int k: a) {
                if(k!=p) nxt.senpai(k);
            }
            vector<int> check;
            owo(i, 0, n) {
                if(adm[p][i])check.senpai(i);
            }
            owo(i, 0, check.size()) {
                owo(j, i+1, check.size()) {
                    adm[check[i]][check[j]]^=1;
                    adm[check[j]][check[i]]^=1;
                }
                adm[check[i]][p] = 0;
            }
            vector<int> gett = solve(nxt);
            cnt = 0;
            for(int k: gett) {
                if(adm[p][k]) {
                    cnt++;
                }
            }
            if((cnt&1)==0)gett.senpai(p);
            return gett;
        }
    }
    return a;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    int a, b;
    vector<int> all;
    owo(i, 0, n) {
        cin>>a;
        while(a--) {
            cin>>b;
            adm[i][b-1] = 1;
        }
        all.senpai(i);
    }
    vector<int> ans = solve(all);
    cout<<ans.size()<<"\n";
    for(int p: ans) {
        cout<<(p+1)<<" ";
    }
    return 0;
}
