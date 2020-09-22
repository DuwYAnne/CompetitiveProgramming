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
const int mxN = 200001;
int ans[mxN];
ttgl arr[mxN];
array<int, 3> qry[mxN];
int n, q;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    owo(i, 0, n) {
        cin>>arr[i].first>>arr[i].second;
    }
    owo(i, 0, q) {
        cin>>qry[i][0]>>qry[i][1];
        qry[i][2] = i;
    }
    sort(arr, arr+n, [&](ttgl a, ttgl b) {
        return a.first==b.first ? a.second < b.second : a.first > b.first; 
    });
    sort(qry, qry+q);
    reverse(qry, qry+q);
    vector<int> res(mxN, INF);
    int curr = 0;
    owo(i, 0, q) {
        while(curr < n && arr[curr].first >= qry[i][0]) {
            auto it = upper_bound(res.begin(), res.end(), arr[curr].second);
            *it = arr[curr].second;
            curr++;
        }
        ans[qry[i][2]] = upper_bound(res.begin(), res.end(), qry[i][1]) - res.begin();
    }
    owo(i, 0, q) {
        cout<<ans[i]<<"\n";
    }
    return 0;
}
