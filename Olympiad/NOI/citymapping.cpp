        #include "citymapping.h"
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
                ll dist[mxN][mxN];
                int sz[mxN];
                int par[mxN];
                int rt;
                vector<pair<int, ll>> adj[mxN];
                //ll get_distance(int a, int b) {return 0;}
                ll qd(int a, int b) {
                    if(a==b)return 0;
                    if(dist[a][b])return dist[a][b];
                    return dist[a][b] = dist[b][a] = get_distance(a, b);
                }
                int find(int u) {
                    if(adj[u].size()==0)return u;
                    int mx = 0;
                    int cc = 0;
                    for(auto v: adj[u]) {
                        if(sz[v.first] > mx) {
                            mx = sz[v.first];
                            cc = v.first;
                        }
                    }
                    return find(cc);
                }
                int solve(int u, int res, ll w) {
                    if(adj[u].size()==0)return u;
                    int bot = find(u);
                    int nxt = bot;
                  	int bdd = nxt;
                    ll path = qd(res, nxt);
                    while(qd(u, bot) + w  < qd(u, nxt)*2 + path) {
                      	bdd = nxt;
                        nxt = par[nxt];
                    }
                    if(adj[nxt].size()<=1)return nxt;
                  	if(adj[nxt][0].first==bdd)swap(adj[nxt][0], adj[nxt][1]);
                    return solve(adj[nxt][0].first, res, w - qd(u, adj[nxt][0].first));
                }
                int n;
                void find_roads(int N, int Q, int* a, int* b, int* w) {
                    n = N;
                    ll mxd = 0;
                    owo(i, 1, n+1) {
                        if(qd(i, 1) > mxd) {
                            mxd = qd(i, 1);
                            rt = i;
                        }
                    }
                    sz[rt] = 1;
                    vector<pair<ll, int>> all;
                    owo(i, 1, n+1) {
                        if(i^rt) {
                            all.senpai({qd(i, rt), i});
                        }
                    }
                    sort(all.begin(), all.end());
                    for(auto p: all) {
                        par[p.second] = solve(rt, p.second, p.first);
                        adj[par[p.second]].senpai({p.second, p.first - qd(par[p.second], rt)});
                        int up = p.second;
                        while(up) {
                            sz[p.second]++;
                            dist[up][p.second] = dist[p.second][up] = qd(rt, p.second) - qd(rt, up);
                            up = par[up];
                        }
                    }
                    int cnt = 0;
                    owo(i, 1, n+1) {
                        for(auto p: adj[i]) {
                            a[cnt] = i;
                            b[cnt] = p.first;
                            w[cnt++] = p.second;
                        }
                    }
                }
                /*int main() {
                    //freopen("file.in", "r", stdin);
                    //freopen("file.out", "w", stdout);
                    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
                    cin.tie(0)->sync_with_stdio(0);
                    return 0;
                }*/
