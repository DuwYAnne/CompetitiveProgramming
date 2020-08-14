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
    const int mxN = 500;
    int st = -1;
    int adj[mxN][mxN];
    int cnt[mxN];
    int num[mxN][mxN];
    int par[mxN][mxN];
    bool state[mxN][mxN][2];
    //state = [cop_pos, robber_pos]
    //0 is cop's turn
    //1 is robber's turn
    int n;
    int start(int N, bool A[mxN][mxN]) {
        n= N;
        queue<array<int, 3>> Q;
        owo(i, 0, n) {
            owo(j, 0, n) {
                adj[i][j] = A[i][j];
                cnt[i]+=adj[i][j];
            }
            state[i][i][0] = true;
            state[i][i][1] = true;
            Q.push({i, i, 0});
            Q.push({i, i, 1});
        }
        while(!Q.empty()) {
            auto p = Q.front();
            Q.pop();
            if(p[2]==0) {
                owo(i, 0, n) {
                    if(adj[p[1]][i]) {
                        if(state[p[0]][i][1])continue;
                        num[p[0]][i]++;
                        if(num[p[0]][i]==cnt[i]) {
                            state[p[0]][i][1] = true;
                            Q.push({p[0], i, 1});
                        }
                    }
                }
            }else {
                owo(i, 0, n) {
                    if(adj[p[0]][i]||i==p[0]) {
                        if(state[i][p[1]][0])continue;
                        state[i][p[1]][0] = true;
                        par[i][p[1]] = p[0];
                        Q.push({i, p[1], 0});
                    }
                }
            }
        }
        owo(i, 0, n) {
            owo(j, 0, n) {
                if(!state[i][j][0])break;
                if(j==n-1)st = i;
            }
        }
        return st;
    }
    int nextMove(int R) {
        return st = par[st][R];
    }
    /*int main() {
        int N;
        cin >> N;
        bool A[mxN][mxN];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> A[i][j];
            }
        }
        int P = start(N,A);
        int curr = -1;
        while(st!=curr) {
            cout<<"cop: "<<st<<"\n";
            cin>>curr;
            nextMove(curr);
        }
        cout << P << endl;
        int R;
        cin >> R;
        while (true) {
            if (P == R) break;
            P = nextMove(R);
            cout << P << endl;
            if (P == R) break;
            cin >> R;
        }
    }*/
