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
int n, m, q;
int cnt[2*mxN];
int grid[mxN][mxN];
int ok[mxN][mxN];
int ak[mxN][mxN];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool inside(int a, int b) {
    return a>=0&&a<n&&b>=0&&b<m;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    owo(i, 0, n) {
        owo(j, 0, m) {
            cin>>grid[i][j];
        }
    }
    queue<pair<int, int>> Q;
    ak[n-1][m-1] = 1;
    Q.push({n-1, m-1});
    while(!Q.empty()) {
        auto[x, y] = Q.front();
        Q.pop();
        owo(d, 2, 4) {
            if(inside(x + dx[d], y + dy[d]) && grid[x + dx[d]][y + dy[d]] == 0) {
                if(ak[x + dx[d]][y + dy[d]] == 0) {
                    Q.push({x + dx[d], y + dy[d]});
                }
                ak[x + dx[d]][y + dy[d]]++;
            }
        }
    }
    ok[0][0] = 1;
    Q.push({0, 0});
    while(!Q.empty()) {
        auto[x, y] = Q.front();
        Q.pop();
        owo(d, 0, 2) {
            if(inside(x + dx[d], y + dy[d]) && grid[x + dx[d]][y + dy[d]] == 0 && ak[x + dx[d]][y + dy[d]]) {
                if(ok[x + dx[d]][y + dy[d]] == 0) {
                    Q.push({x + dx[d], y + dy[d]});
                }
                ok[x + dx[d]][y + dy[d]]++;
            }
        }
    }
    owo(i, 0, n) {
        owo(j, 0, m) {
            //cout<<i<<" "<<j<<" "<<ok[i][j]<<"\n";
            cnt[i + j] += (ok[i][j] ? 1 : 0);
        }
    }
    int a, b;
    cin>>q;
    while(q--) {
        cin>>a>>b;
        a--; b--;
        //cout<<"nxt------------------- \n";
        //cout<<a<<" "<<b<<"\n";
        if(cnt[a + b]==1 && ok[a][b]) {
            cout<<"0\n";
        }else {
            cout<<"1\n";
            grid[a][b] = 1;
            if(ok[a][b]==0)continue;
            ok[a][b] = 0;
            Q.push({a, b});
            while(!Q.empty()) {
                auto[x, y] = Q.front();
                Q.pop();
                cnt[x + y]--;
                owo(d, 0, 2) {
                    if(inside(x + dx[d], y + dy[d]) && grid[x + dx[d]][y + dy[d]] == 0 && ak[x + dx[d]][y + dy[d]]) {
                        if(--ok[x + dx[d]][y + dy[d]] == 0) {
                            Q.push({x + dx[d], y + dy[d]});
                        }
                    }
                }
            }
            ak[a][b] = 0;
            Q.push({a, b});
            while(!Q.empty()) {
                auto[x, y] = Q.front();
                if(ok[x][y]) {
                    cnt[x + y]--;
                }
                ok[x][y] = 0;
                Q.pop();
                owo(d, 2, 4) {
                    if(inside(x + dx[d], y + dy[d]) && grid[x + dx[d]][y + dy[d]] == 0) {
                        if(--ak[x + dx[d]][y + dy[d]] == 0) {
                            Q.push({x + dx[d], y + dy[d]});
                        }
                    }
                }
            }
        }
    }
    return 0;
}
