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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
gpu_hash_table<int, int> mp;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 */
using ll = long long;
using ld = long double;
const ll MOD = 924844033;
const ll root = 62;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 401;
int dist[mxN][mxN];
array<int, 3> prv[mxN][mxN];
bool flag[mxN][mxN][27];
vector<int> adj[mxN][26];
vector<int> radj[mxN][26];
int n, m;
queue<array<int, 4>> Q;
string alph = "abcdefghijklmnopqrstuvwxyz";
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int a, b;
    char c;
    memset(dist, INF, sizeof(dist));
    owo(i, 0, m) {
        cin>>a>>b>>c;
        a--; b--;
        adj[a][c-'a'].senpai(b);
        radj[b][c-'a'].senpai(a);
    }
    owo(i, 0, n) {
        dist[i][i] = 0;
        Q.push({i, i, -1, -1});
        prv[i][i] = {-1, -1, -1};
    }
    owo(i, 0, n) {
        owo(j, 0, 26) {
            for(int v: adj[i][j]) {
                if(dist[i][v]==INF) {
                    dist[i][v] = 1;
                    prv[i][v] = {j, -1, -1};
                    //cout<<i<<" "<<v<<"\n";
                    Q.push({i, v, -1, -1});
                }
            }
        }
    }
    while(!Q.empty()) {
        auto p = Q.front();
        Q.pop();
        if(p[3]==-1) {
            owo(ch, 0, 26) {
                for(int u: radj[p[0]][ch]) {
                    if(flag[p[1]][u][ch])continue;
                    flag[p[1]][u][ch] = true;
                    Q.push({p[0], p[1], u, ch});
                }
            }
        }else {
                //cout<<p[1]<<" "<<alph[p[3]-1]<<"\n";
            for(auto v: adj[p[1]][p[3]]) {
                if(dist[p[2]][v]!=INF)continue;
                dist[p[2]][v] = dist[p[0]][p[1]]+2;
                prv[p[2]][v] = {p[3], p[0], p[1]};
                Q.push({p[2], v, -1, -1});
            }
        }
    }
    int q;
    cin>>q;
    int last;
    cin>>last;
    last--;
    q--;
    while(q--) {
        cin>>a;
        a--;
        vector<char> res;
        int curr1 = last;
        int curr2 = a;
        if(dist[last][a]!=INF) {
            while(true) {
                int nxt1 = prv[curr1][curr2][1];
                int nxt2 = prv[curr1][curr2][2];
                //cout<<curr1<<" "<<curr2<<" "<<prv[curr1][curr2].first<<" "<<prv[curr1][curr2].second.first<<" "<<prv[curr1][curr2].second.second<<"\n";
                if(nxt1==-1) {
                    if(prv[curr1][curr2][0]!=-1) {
                        res.senpai(prv[curr1][curr2][0]);
                    }
                    break;
                }else {
                    res.senpai(prv[curr1][curr2][0]);
                    curr1 = nxt1;
                    curr2 = nxt2;
                }
            }
            cout<<dist[last][a]<<" ";
            owo(i, 0, dist[last][a]/2) {
                cout<<alph[res[i]];
            }
            if(dist[last][a]&1)cout<<alph[res[res.size()-1]];
            uwu(i, dist[last][a]/2, 0) {
                cout<<alph[res[i]];
            }
            cout<<"\n";
        }else {
            cout<<"-1\n";
        }
        last = a;
    }
    return 0;
}
