#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> mp;*/
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 101;
int dp[mxN][mxN][51]; 
int save[mxN];
/*
dp(i, j, k) = min cost to have the nodes in the subtree of node i be sent up to j given that there are k sawmills blocking some of them
At each step, we can take each descendant as totally blocked, dp[i][i][k], or take it as its own min dp[i][j][k].
*/
vector<int> anc[mxN];
vector<int> adj[mxN];
int dist[mxN][mxN];
int sz[mxN];
int par[mxN];
int val[mxN];
int n, k;
void solve(int u) {
    sz[u] = 1;
    for(int v: adj[u]) {
        solve(v);
    }
    for(int p: anc[u]) {
        sz[u] = 1;
        for(int v: adj[u]) {
            owo(i, 0, min(sz[u]+sz[v]+1, 51)) {
                save[i] = INF;
            }
            owo(i, 0, sz[u]) {
                owo(j, 0, sz[v]+1) {
                    if(i+j>50)break;
                    save[i+j]  = min(save[i+j], dp[u][p][i] + dp[v][p][j]);
                    if(j>0) {//here we try putting a sawmill on the child
                        save[i+j] = min(save[i+j], dp[u][p][i] + dp[v][v][j-1]);
                    }
                    //cout<<i<<" "<<j<<" "<<save[i+j]<<"\n";
                }
            }
            owo(i, 0, min(sz[u]+sz[v]+1, 51)) {
                dp[u][p][i] = save[i];
            }
            sz[u]+=sz[v];
        }
        owo(i, 0, min(sz[u], 51)) {
            dp[u][p][i] +=dist[u][p]*val[u];
            //cout<<u<<" "<<p<<" "<<i<<" "<<dp[u][p][i]<<"\n";
        }
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    int a, b, c;
    owo(i, 1, n+1) {
        cin>>a>>b>>c;
        par[i] = b;
        val[i] = a;
        dist[i][b] = c;
        adj[b].senpai(i);
    }
    anc[0].senpai(0);
    owo(i, 1, n+1) {
        int curr = par[i];
        anc[i].senpai(i);
        anc[i].senpai(curr);
        while(curr!=0) {
            dist[i][par[curr]] = dist[i][curr] + dist[curr][par[curr]];
            curr = par[curr];
            anc[i].senpai(curr);
        }
        //cout<<i<<" eye----------\n";
        for(int p: anc[i]) {
            //cout<<p<<" "<<dist[i][p]<<"\n";
        }
    }
    solve(0);
    cout<<dp[0][0][k]<<"\n";
    return 0;
}
