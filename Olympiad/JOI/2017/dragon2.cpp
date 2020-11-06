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
    #define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
     
    using ll = long long;
    using ld = long double;
    const ll MOD = 1000000007;
    const ll root = 62;
    ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
    ll modInv(ll a){return binpow(a, MOD-2);}
    const double PI = atan(1);
    const double eps = 1e-10;
    const int INF = 0x3f3f3f3f;
    const int NINF = 0xc0c0c0c0;
    const ll INFLL = 0x3f3f3f3f3f3f3f3f;
    const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
    const int mxN = 30001;
    struct pt {
        ll x, y;
        pt(ll x = 0, ll y = 0) : x(x), y(y) {}
        bool operator < (const pt &o) const {
            return (x == o.x ? y < o.y : x < o.x);
        }
        pt operator - (const pt &o) const {
            return pt(x - o.x, y - o.y);
        }
    };
    ll cross(pt a, pt b) {
        return a.x * b.y - a.y * b.x;
    }
    bool ccw(pt &a, pt &b, pt &c) {
        return cross(a-b, c-b) <= 0;
    }
    vector<pt> tribe[mxN];
    int n, m, q;
    pt x, y;
    bool chk(pt &a, pt &b) {
        if(ccw(a, x, y)) {
            if(ccw(a, x, b) && ccw(b, y, a))return 1;
        }else {
            if(ccw(b, x, a) && ccw(a, y, b))return 1;
        }
        return 0;
    }
    int main() {
        //freopen("file.in", "r", stdin);
        //freopen("file.out", "w", stdout);
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        cin.tie(0)->sync_with_stdio(0);
        scanf("%d %d\n", &n, &m);
        int a, b, c;
        owo(i, 0, n) {
            scanf("%d %d %d\n", &a, &b, &c);
            tribe[c].senpai({a, b});
        }
        scanf("%lld %lld %lld %lld\n", &x.x, &x.y, &y.x, &y.y);
        scanf("%d\n", &q);
        while(q--) {
            scanf("%d %d\n", &a, &b);
                int res = 0;
                for(auto &k1: tribe[a]) {
                    for(auto &k2: tribe[b]) {
                        res+=chk(k1, k2);
                    }
                }
                printf("%d \n", res);
        }
        return 0;
    }
