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
const int mxN = 100001;
int n;
int arr[mxN];
ll BIT[mxN];
void upd(int p, ll val) {
    p++;
    while(p<=n) {
        BIT[p]+=val;
        p+=p&-p;
    }
}
ll query(int p) {
    p++;
    ll res = 0;
    while(p>0) {
        res+=BIT[p];
        p-=p&-p;
    }
    return res;
}
ll ans = 0;
vector<int> poss;
void solve(int l, int r, int optl, int optr) {
    if(l>r) {
        owo(i, optl, optr+1) {
            upd(arr[i], 1);
        }
        return;
    }
    int mid = (l+r)/2;
    int opt = -1;
    ll best = -1;
    owo(i, poss[l], poss[mid]) {
        upd(arr[i], -1);
    }
    owo(i, optl, optr+1) {
        upd(arr[i], 1);
        ll k1 = query(arr[poss[mid]]-1) + query(arr[poss[mid]]) - query(arr[i]-1) - query(arr[i]);
        if(k1>=best) {
            best = k1;
            opt = i;
        }
    }
    //cout<<best<<" "<<opt<<"\n";
    ans = min(1LL-best, ans);
    owo(i, poss[l], poss[mid]) upd(arr[i], 1);
    owo(i, optl, optr+1) upd(arr[i], -1);
    solve(l, mid-1, optl, opt);
    owo(i, poss[mid], poss[mid+1]) upd(arr[i], -1);
    upd(arr[opt], -1);
    solve(mid+1, r, opt, optr);
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    set<int> ss;
    bool bad = 1;
    owo(i, 0, n) {
        cin>>arr[i];
        ss.insert(arr[i]);
        if(i&&arr[i]<arr[i-1]) {
            bad = 0;
        }
    }
    if(bad) {
        int k = 0;
        owo(i, 0, n-1) {
            if(arr[i]==arr[i+1])k = 1;
        }
        k^=1;
        cout<<k<<"\n";
        exit(0);
    }
    vector<int> o(ss.begin(), ss.end());
    owo(i, 0, n) {
        arr[i] = lower_bound(o.begin(), o.end(), arr[i])-o.begin();
    }
    owo(i, 0, n) {
        if(poss.size()==0||arr[i]>arr[poss.back()]) {
            //cout<<i<<"\n";
            poss.senpai(i);
        }
    }
    poss.senpai(n);
    solve(0, poss.size()-2, 0, n-1);
    uwu(i, n, 0) {
        ans+=query(arr[i]-1);
        upd(arr[i], 1);
    }
    cout<<ans<<"\n";
    return 0;
}
