    #pragma GCC target ("avx2")
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
    const int mxA = 10000001;
    int id[mxA];
    int arr[mxA];
    vector<int> all;
    int n;
    vector<ttgl> edges[mxA];
    int dsu[mxN];
    int find(int a) {
        return a==dsu[a] ? a : dsu[a] = find(dsu[a]);
    }
    void merge(int a, int b) {
        dsu[find(b)] = find(a);
    }
    int main() {
        //freopen("file.in", "r", stdin);
        //freopen("file.out", "w", stdout);
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        cin.tie(0)->sync_with_stdio(0);
        cin>>n;
        int maxval = 0;
        all.resize(n);
        owo(i, 0, n) {
            cin>>all[i];
            maxval = max(maxval, all[i]);
        }
        owo(i, 0, n) {
            dsu[i] = i;
        }
        sort(all.begin(), all.end());
        all.resize(unique(all.begin(), all.end()) - all.begin());
        n= all.size();
        owo(i, 0, all.size())id[all[i]] = i;
        owo(i, 0, n-1) {
            int nxt = i+1;
            for(int j=all[i]; j<=maxval; j+=all[i]) {
                while(all[nxt]<j)nxt++;
                edges[all[nxt]%all[i]].senpai({i, nxt});
            }
        }
        ll ans = 0;
        owo(i, 0, maxval+1) {
            for(auto p: edges[i]) {
                if(find(p.first)!=find(p.second)) {
                    ans+=i;
                    merge(p.first, p.second);
                }
            }
        }
        cout<<ans<<"\n";
        return 0;
    }
