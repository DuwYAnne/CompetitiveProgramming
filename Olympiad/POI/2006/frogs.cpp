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
const int mxN = 1001;
//first do d&c, then binary search reachability
int w, h, m;
int dist[mxN][mxN];
int hdist[mxN][mxN];
bool ok[mxN][mxN];
ttgl s, t;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool inside(int x, int y) {
    return x>=0&&x<w&&y>=0&&y<h;
}
bool check(int mxd) {
    memset(ok, false, sizeof(ok));
    //cout<<mxd<<"\n";
    ok[s.first][s.second] = true;
    queue<pair<int, int>> Q;
    Q.push(s);
    while(!Q.empty()) {
        auto[x, y] = Q.front();
        Q.pop();
        owo(d, 0, 4) {
            if(inside(x + dx[d], y + dy[d]) && (!ok[x + dx[d]][y + dy[d]]) && (dist[x + dx[d]][y + dy[d]] >= mxd)) {
                ok[x + dx[d]][y + dy[d]] = true;
                Q.push({x + dx[d], y + dy[d]});
            }
        }
    }
    return ok[t.first][t.second];
}
void recurse(int i, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l + r) >> 1;
    ttgl best = {INF, 0};
    owo(j, optl, optr+1) {
        if(hdist[j][i]==INF)continue;
        best = min(best, make_pair((j-mid)*(j-mid) + hdist[j][i]*hdist[j][i], j));
    }
    dist[mid][i] = best.first;
    recurse(i, l, mid-1, optl, best.second);
    recurse(i, mid+1, r, best.second, optr);
}
int main() {
    //freopen("disconnect.in", "r", stdin);
    //freopen("disconnect.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>w>>h;
    cin>>s.first>>s.second>>t.first>>t.second;
    s.first--; s.second--; t.first--; t.second--;
    cin>>m;
    queue<int> Q[mxN];
    int a, b;
    memset(dist, INF, sizeof(dist));
    memset(hdist, INF, sizeof(hdist));
    owo(i, 0, m) {
        cin>>a>>b;
        a--; b--;
        Q[a].push(b);
        hdist[a][b] = 0;
    }
    owo(i, 0, w) {
        while(!Q[i].empty()) {
            int y = Q[i].front();
            Q[i].pop();
            if(inside(i, y - 1) && hdist[i][y - 1]==INF) {
                hdist[i][y - 1] = hdist[i][y] + 1;
                Q[i].push(y - 1);
            }
            if(inside(i, y + 1) && hdist[i][y + 1]==INF) {
                hdist[i][y + 1] = hdist[i][y] + 1;
                Q[i].push(y + 1);
            }
        }
    }
    owo(i, 0, h) {
        recurse(i, 0, w-1, 0, w-1);
    }
    int l = 0;
    int r = min(dist[s.first][s.second], dist[t.first][t.second]);
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if(check(mid)) {
            l = mid;
        }else {
            r = mid - 1;
        }
    }
    cout<<(l)<<"\n";
    return 0;
}
