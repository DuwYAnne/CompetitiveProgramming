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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 
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
const int mxN = 2000000;
int n;
int arr[mxN];
int prv[mxN];
int pst[mxN];
set<int> lev[mxN * 2];
vector<int> at[mxN];
vector<ttgl> ans;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i];
        prv[i] = i - 1;
        while(prv[i] >= 0 && arr[prv[i]] < arr[i]) prv[i] = prv[prv[i]];
        at[prv[i] + 1].senpai(i);
    }
    uwu(i, n, 0) {
        pst[i] = i + 1;
        while(pst[i] < n && arr[pst[i]] > arr[i]) pst[i] = pst[pst[i]];
    }
    owo(i, 0, n) {
        //insert right bounds at this point
        for(int k: at[i]) {
            lev[arr[k] - k + mxN].insert(k);
        }
        auto it = lev[arr[i] - i + mxN].upper_bound(i);
        if(it == lev[arr[i] - i + mxN].end())continue;
        if(*it >= pst[i])continue;
        while(ans.size() && i < ans.back().second) {
            ans.pop_back();
        }
        ans.senpai({i, *it});
    }
    cout<<ans.size()<<"\n";
    for(auto p: ans) {
        cout<<(p.first + 1)<<" "<<(p.second + 1)<<"\n";
    }
    return 0;
}
