#include <bits/stdc++.h>
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> mp;
using ll = long long;
using ld = long double;
const ll MOD = 1000000007;
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
const int mxN = 101;
const int mxK = 1001;
vector<ttgl> adj[mxN];
ll graph[mxN][mxN];
int best[mxN][mxN];
int dist[mxN][mxN];
ll findist[mxN][mxN];
int stuff[mxN][2][mxK];
int n, m, k;
bool check(int tt) {
    owo(i, 0, n) {
        owo(j, 0, n) {
            if(i==j)  {
                graph[i][j] = 1;
            }else if(dist[i][j]!=INF) {
                graph[i][j] = -(best[i][j]-1LL*dist[i][j]*tt);
            }else {
                graph[i][j] = INFLL;
            }
            //cout<<i<<" "<<j<<" "<<graph[i][j]<<" "<<dist[i][j]<<" "<<best[i][j]<<"\n";
            findist[i][j] = graph[i][j];
        }
    }
    owo(k, 0, n) owo(i, 0, n) owo(j, 0, n) {
        if (findist[i][k] + findist[k][j] < findist[i][j]) {
            findist[i][j] = findist[i][k] + findist[k][j];
        }
    }
    owo(i, 0, n) {
        if(findist[i][i]<=0)return true;
    }
    return false;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    owo(i, 0, n) {
        owo(j, 0, 2*k) {
            cin>>stuff[i][j&1][j/2];
        }
    }
    int a, b, c;
    owo(i, 0, m) {
        cin>>a>>b>>c;
        a--; b--;
        adj[a].senpai({b, c});
    }
    memset(best, -1, sizeof(best));
    memset(dist, INF, sizeof(dist));
    owo(i, 0, n) {
        dist[i][i] = 0;
        priority_queue<ttgl, vector<ttgl>, greater<ttgl>> pq;
        pq.push({0, i});
        while(!pq.empty()) {
            auto p = pq.top();
            //cout<<i<<" "<<p.second<<" "<<p.first<<"\n";
            pq.pop();
            if(p.first!=dist[i][p.second])continue;
            if(p.second!=i) {
                best[i][p.second] = 0;
                owo(nn, 0, k) {
                    if(stuff[i][0][nn]!=-1&&stuff[p.second][1][nn]!=-1) {
                        //cout<<i<<" "<<p.second<<" "<<stuff[p.second][1][nn]<<" "<<stuff[i][0][nn]<<"\n";
                        best[i][p.second] = max(best[i][p.second], stuff[p.second][1][nn]-stuff[i][0][nn]);   
                    }
                }
            }
            for(auto v: adj[p.second]) {
                if(dist[i][p.second] + v.second<dist[i][v.first]) {
                    dist[i][v.first] = dist[i][p.second]+v.second;
                    pq.push({dist[i][v.first], v.first});
                }
            }
        }
    }
    check(2);
    int l = 0;
    int r = INF;
    while(l<r) {
        int mid = (l+r+1)/2;
        if(check(mid)) l = mid;
        else r = mid-1;
    }
    cout<<l<<"\n";
    return 0;
}
