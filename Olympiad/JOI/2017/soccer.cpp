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
const int mxN = 100001;
const int mxV = 501;
int n;
int dist[mxV][mxV];
ttgl per[mxN];
//we can represent a state the following way, x, y, movement, cost
struct state {
    int x, y, dir;
    ll w;
    bool operator <(const state &o) const {
        return w > o.w;
    }
};
int h, w;
ll a, b, c;
ll dp[mxV][mxV][6];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool inside(int x, int y) {
    return x>=0&&x<=h&&y>=0&&y<=w;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>h>>w>>a>>b>>c>>n;
    queue<array<int, 3>> Q;
    memset(dist, INF, sizeof(dist));
    memset(dp, INFLL, sizeof(dp));
    owo(i, 0, n) {
        cin>>per[i].first>>per[i].second;
        Q.push({per[i].first, per[i].second, 0});
        dist[per[i].first][per[i].second] = 0;
    }
    while(!Q.empty()) {
        auto[x, y, currd] = Q.front();
        Q.pop();
        owo(d, 0, 4) {
            if(inside(x + dx[d], y + dy[d]) && dist[x + dx[d]][y + dy[d]] == INF) {
                dist[x + dx[d]][y + dy[d]] = currd + 1;
                Q.push({x + dx[d], y + dy[d], currd + 1});
            }
        }
    }
    priority_queue<state> pq;
    pq.push({per[0].first, per[0].second, 0, 0});
    dp[per[0].first][per[0].second][0] = 0;
    while(!pq.empty()) {
        auto [x, y, dir, currd] = pq.top();
        pq.pop();
        if(currd > dp[x][y][dir])continue;
        if(dir==0) {
            owo(d, 0, 4) {
                if(inside(x + dx[d], y + dy[d])) {
                    //kick
                    if(dp[x][y][d + 2] > currd + b) {
                        dp[x][y][d + 2] = currd + b;
                        pq.push({x, y, d + 2, currd + b});
                    }
                    //run
                    if(dp[x + dx[d]][y + dy[d]][0] > currd + c) {
                        dp[x + dx[d]][y + dy[d]][0] = currd + c;
                        pq.push({x + dx[d], y + dy[d], 0, currd + c});
                    }
                }
                //drop
                if(dp[x][y][1] > currd) {
                    dp[x][y][1] = currd;
                    pq.push({x, y, 1, currd});
                }
            }
        }else if(dir==1) {
            //pick up ball
            if(dp[x][y][0] > currd + 1LL * c * dist[x][y]) {
                dp[x][y][0] = currd + 1LL * c * dist[x][y];
                pq.push({x, y, 0, dp[x][y][0]});
            }
        }else {
            //stop
            if(dp[x][y][1] > currd) {
                dp[x][y][1] = currd;
                pq.push({x, y, 1, currd});
            }
            //roll
            if(inside(x + dx[dir - 2], y + dy[dir - 2]) && dp[x + dx[dir - 2]][y + dy[dir - 2]][dir] > currd + a) {
                dp[x + dx[dir - 2]][y + dy[dir - 2]][dir] = currd + a;
                pq.push({x + dx[dir - 2], y + dy[dir - 2], dir, currd + a});
            }
        }
    }
    ll ans = INFLL;
    owo(i, 0, 6) {
        ans = min(ans, dp[per[n-1].first][per[n-1].second][i]);
    }
    cout<<ans<<"\n";
    return 0;
}
