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
const int mxN = 10001;
const int mxM = 200001;
int ans[mxN][2];
int cnt[mxN][2];
int prv[mxN];
vector<int> adj[mxN];
int n;
void solve(int c) {
    //cout<<"-------------------------------------------------\n";
    memset(cnt, 0, sizeof(cnt));
    ans[0][c] = 0;
    ans[1][c] = 1;
    owo(i, 2, n) {
        ans[i][c] = c;
        prv[i] = c;
    }
    queue<int> Q;
    owo(i, 0, n) {
        for(int j: adj[i]) {
            //cout<<i<<" "<<j<<" "<<col[j]<<"\n";
            cnt[j][ans[i][c]]++;
        }
        //cout<<i<<" "<<col[i]<<" "<<cnt[i][0]<<" "<<cnt[i][1]<<"\n";
    }
    owo(i, 2, n) {
        if(cnt[i][c^1] >= cnt[i][c]) {
            Q.push(i);
        }
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        int pr = prv[u];
        if(cnt[u][0]==cnt[u][1]) {
            ans[u][c] = 2;
        }else if(cnt[u][c^1] > cnt[u][c]) {
            ans[u][c] = c^1;
        }
        if(prv[u] == ans[u][c])continue;
        prv[u] = ans[u][c];
        for(int j: adj[u]) {
            cnt[j][c]-= (pr==c);
            cnt[j][c^1]+=(ans[u][c]==(c^1));
            //cout<<j<<" "<<col[j]<<" "<<cnt[j][0]<<" "<<cnt[j][1]<<"\n";
            if(cnt[j][c^1] > cnt[j][c] && ans[j][c]!=(c^1)) {
                Q.push(j);
                ans[j][c] = c^1;
            }else if(cnt[j][c^1] == cnt[j][c] && ans[j][c] == c) {
                Q.push(j);
                ans[j][c] = 2;
            }
        }
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    int a, k;
    cin>>n;
    owo(i, 2, n) {
        cin>>k;
        owo(j, 0, k) {
            cin>>a;
            adj[a].senpai(i);
        }
    }
    solve(0); solve(1);
    owo(i, 0, n) {
        if(ans[i][0]==ans[i][1]) {
            if(ans[i][0] < 2) {
                cout<<ans[i][0]<<"\n";
            }else {
                cout<<"1/2\n";
            }
        }else {
            cout<<"?\n";
        }
    }
    return 0;
}
