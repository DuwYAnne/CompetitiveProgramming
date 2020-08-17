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
const int mxN = 3001;
int dsu[mxN];
int find(int a) {
    return dsu[a]==a ? a : dsu[a] = find(dsu[a]);
}
bool merge(int a, int b) {
    a = find(a); b = find(b);
    if(a==b)return false;
    dsu[b] = a;
    return true;
}
int arr[mxN][mxN];
int n;
int cnt;
vector<ttgl> ans;
vector<int> adj[mxN];
int col[mxN];
void dfs(int id, int st, int u, int p) {
    if(arr[id][u]==arr[st][u]) {
        //cout<<id<<" "<<u<<" hi\n";
        merge(id, u);
        return;
    }
    for(int v: adj[u]) {
        if(v^p) {
            dfs(id, st, v, u);
        }
    }
}
int ari_orz;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>ari_orz;
    cin>>n;
    owo(i, 0, n) {
        owo(j, 0, n) { 
            cin>>arr[i][j];
        }
    }
    owo(i, 0, n) {
        dsu[i] = i;
    }
    //merge all same color
    owo(i, 0, n) {
        owo(j, 0, n) {
            if(i==j)continue;
            if(arr[i][j]==1&&merge(i, j)) {
                ans.senpai({i, j});
                adj[i].senpai(j);
                adj[j].senpai(i);
            }
        }
    }
    owo(i, 0, n) {
        owo(j, 0, n) {
            if(i==j)continue;
            if(arr[i][j]==2&&merge(i, j)) {
                ans.senpai({i, j});
                adj[i].senpai(j);
                adj[j].senpai(i);
            }
        }
    }
    owo(i, 0, n) {
        dsu[i] = i;
    }
    owo(i, 0, n) {
        for(int k: adj[i]) {
            dfs(i, k, k, i);
        }
    }
    owo(i, 0, n) {
        cout<<(find(i)+1)<<" ";
    }
    cout<<"\n";
    for(auto p: ans) {
        cout<<(p.first+1)<<" "<<(p.second+1)<<"\n";
    }
    
    return 0;
}
