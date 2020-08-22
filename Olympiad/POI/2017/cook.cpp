#include "ckuclib.h"
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
const int mxN = 1000001;
const int logn = 24;
int n, e;
int maxe;
ll dp1[logn][logn];
ll dp2[logn][logn];
int at[logn][2];
/*ll p1[mxN];
ll p2[mxN];
ll p3[mxN];
ll jedno(int a) {
    return p1[a];
}
ll dwa(int a) {
    return p2[a];
}
ll polowa(int a) {
    return p3[a];
}*/
void push(int a) {
    if(at[a][0]==-1) {
        ll k = jedno(1);
        owo(i, 0, maxe+1) {
            dp1[a][i] = k;
        }
        at[a][0] = 1;
    }else if(at[a][1]==-1) {
        owo(i, 0, maxe+1) {
            dp2[a][i] = dp1[a][i];
        }
        at[a][1] = at[a][0];
        ll k1 = jedno(2);
        ll k2 = dwa(2);
        ll k3 = polowa(2);
        owo(i, 0, maxe+1) {
            dp1[a][i] = min(dp2[a][min(i+1, maxe)] + k1, k2);
            if(i) {
                dp1[a][i] = min(dp1[a][i], dp2[a][i-1] + k3);
            }
        }
        at[a][0] = 2;
    }else {
        int to = at[a][0]+1;
        int prv = to-to/2;
        ll state[logn];
        ll k1 = jedno(to);
        ll k2 = dwa(to);
        ll k3 = polowa(to);
        owo(i, 0, maxe+1) {
            state[i] = min(dp1[a][min(i+1, maxe)] + k1, dp2[a][i] + k2);
        }
        if(prv == at[a][0]) {
            owo(i, 1, maxe+1) {
                state[i] = min(state[i], dp1[a][i-1] + k3);
            }   
        }else if(prv == at[a][1]) {
            owo(i, 1, maxe+1) {
                state[i] = min(state[i], dp2[a][i-1] + k3);
            }
        }else {
            //create new segment
            while(at[a+1][0]!=prv)push(a+1);
            owo(i, 1, maxe+1) {
                state[i] = min(state[i], dp1[a+1][i-1] + k3);
            }
        }
        owo(i, 0, maxe+1) {
            dp2[a][i] = dp1[a][i];
            dp1[a][i] = state[i];
        }
        at[a][0]++;
        at[a][1]++;
    }
        /*owo(i, 0, maxe+1) {
            cout<<dp1[a][i]<<" ";
        }
        cout<<"\n";
        owo(i, 0, maxe+1) {
            cout<<dp2[a][i]<<" ";
        }
        cout<<"\n";*/
    //cout<<at[a][0]<<" "<<at[a][1]<<"\n";
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    n = dajn();
    e = daje();
    /*cin>>n>>e;
    owo(i, 1, n+1) {
        cin>>p1[i];
    }
    owo(i, 1, n+1) {
        cin>>p2[i];
    }
    owo(i, 1, n+1) {
        cin>>p3[i];
    }*/
    maxe = 0;
    while(n>(1<<maxe)) maxe++;
    maxe++;
    //cout<<maxe<<"\n";
    memset(at, -1, sizeof(at));
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    owo(i, 0, n) {
        push(1);
    }
    //cout<<(dp1[1][min(e, maxe)])<<"\n";
    odpowiedz(dp1[1][min(e,maxe)]);
    return 0;
}
