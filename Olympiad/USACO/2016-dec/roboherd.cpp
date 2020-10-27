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
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
ll ans = 0;
int n, k;
vector<vector<int>> m;
//consider the next possible search spaces after taking some min robot
//lets start with the robot taking the min increase area
//then we have a few choices: switch to the next microcontroller on the same area
//go to the next area with 0 on this area, can only be done if we are one first part, since its sorted
//go to next area maintaining current area.
int main() {
    freopen("roboherd.in", "r", stdin);
    freopen("roboherd.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    m.resize(n);
    ll first = 0;
    vector<vector<int>> all;
    owo(i, 0, n) {
        int a;
        cin>>a;
        m[i].resize(a);
        owo(j, 0, a) {
            cin>>m[i][j];
        }
        sort(m[i].begin(), m[i].end());
        first+=m[i][0];
        uwu(j, a, 0) {
            m[i][j]-=m[i][0];
        }
        if(m[i].size() > 1) {
            all.senpai(m[i]);
        }
    }
    sort(all.begin(), all.end());
    ll ans = first;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    pq.push({first + all[0][1], 0, 1});
    k--;
    while(k--) {
        auto p = pq.top();
        ll cst = p[0];
        ll x = p[1]; 
        ll y = p[2];
        pq.pop();
        ans+=cst;
        if(y + 1 < all[x].size()) {
            pq.push({cst - all[x][y] + all[x][y+1], x, y+1});
        }
        //move to next area
        if(x + 1 < all.size()) {
            if(y == 1) {//this one has 0
                pq.push({cst - all[x][y] + all[x+1][y], x+1, y});
            }
            pq.push({cst + all[x+1][1], x+1, 1});
        }
    }
    cout<<ans<<"\n";
    return 0;
}
