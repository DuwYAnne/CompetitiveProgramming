    #include "wombats.h"
    #pragma GCC target ("avx2")
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
    const ll MOD = 998244353;
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
    const int mxR = 5000;
    const int mxC = 200;
    const int BLOCK = 10;
    const int sgsz = 500;
    int h[mxR][mxC], v[mxR][mxC], seg[1024][mxC][mxC], opt[mxC + 1];
    void upd(int l, int r, int le = 0, int rr = sgsz-1, int i = 1) {
        if(le > r||rr < l)return;
        if(le==rr) {
            //brute force this BLOCK
            memset(seg[i], INF, sizeof(seg[i]));
            owo(j, 0, mxC) {
                seg[i][j][j] = 0;
                owo(k, le*BLOCK, le*BLOCK + BLOCK) {
                    owo(b, 1, mxC) {
                        seg[i][j][b] = min(seg[i][j][b], seg[i][j][b-1] + h[k][b-1]);
                    }
                    uwu(b, mxC, 1) {
                        seg[i][j][b-1] = min(seg[i][j][b-1], seg[i][j][b] + h[k][b-1]);
                    }
                    owo(b, 0, mxC) {
                        seg[i][j][b] += v[k][b];
                    }
                }
            }
            return;
        }
        int mid = (le + rr) >> 1;
        upd(l, r, le, mid, 2*i);
        upd(l, r, mid+1, rr, 2*i+1);
        memset(opt, 0, 4*mxC);
        owo(j, 0, mxC) {
            for(int k = mxC - 1; ~k; --k) {
                ttgl best = {INF, 0};
                owo(b, opt[k], opt[k+1] + 1) {
                    best = min(best, {seg[2*i][j][b] + seg[2*i+1][b][k], -b});
                }
                seg[i][j][k] = best.first;
                opt[k] = -best.second;
            }
        }
    }
    void init(int r, int c, int H[5000][200], int V[5000][200]) {
        memset(h, INF, sizeof(h));
        owo(i, 0, r) {
            owo(j, 0, c-1) {
                h[i][j] = H[i][j];
            }
        }
        owo(i, 0, r-1) {
            owo(j, 0, c) {
                v[i][j] = V[i][j];
            }
        }
        opt[mxC] = mxC-1;
        upd(0, sgsz-1);
    }
    void changeH(int p, int q, int w) {
        h[p][q] = w;
        upd(p/BLOCK, p/BLOCK);
    }
    void changeV(int p, int q, int w) {
        v[p][q] = w;
        upd(p/BLOCK, p/BLOCK);
    }
    int escape(int a, int b) {
        return seg[1][a][b];
    }
