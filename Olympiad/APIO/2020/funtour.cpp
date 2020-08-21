//untested and unsubmitted, waiting for an OJ to add

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
const int mxN = 100001;
/*int attractionsBehind(int a, int b) {
    return 1;
}
int hoursRequired(int a, int b) {
    return 1;
}*/
int n;
int sz[mxN];
int dist[mxN];
vector<ttgl> all[3];
void finish(vector<int> &res, vector<ttgl> fst, vector<ttgl> snd, bool at) {
    while(fst.size()||snd.size()) {
        if(at) {
            res.senpai(snd.back().second);
            snd.pop_back();
        }else {
            res.senpai(fst.back().second);
            fst.pop_back();
        }
        at^=1;
    }
}
vector<int> createFunTour(int N, int q) {
    vector<int> res;
    n = N;
    owo(i, 1, n) {
        sz[i] = attractionsBehind(0, i);
    }
    int cent = 0;
    int bestsz = INF;
    owo(i, 1, n) {
        if(sz[i]>=n/2&&sz[i]<bestsz) {
            cent = i;
            bestsz = sz[i];
        }
    }
    vector<int> subs;
    owo(i, 0, n) {
        if(i^cent) {
            dist[i] = hoursRequired(cent, i);
            if(dist[i]==1) {
                subs.senpai(i);
            }
        }
    }
    int totsz = n-1;
    owo(i, 0, n) {
        if(dist[i]==0)continue;
        int a = hoursRequired(i, subs[0]);
        int b = hoursRequired(i, subs[1]);
        if(a==dist[i]-1) {
            all[0].senpai({dist[i], i});
        }else if(b==dist[i]-1) {
            all[1].senpai({dist[i], i});
        }else {
            all[2].senpai({dist[i], i});
        }
    }
    owo(i, 0, 3) {
        sort(all[i].begin(), all[i].end());
    }
    
    int prv = -1;
    while(1) {
        array<int, 3> best = {-1, -1, -1};
        if(prv!=0&&all[0].size()) {
            best = max(best, {all[0].back().first, all[0].back().second, 0});
        }
        if(prv!=1&&all[1].size()) {
            best = max(best, {all[1].back().first, all[1].back().second, 1});
        }
        if(prv!=2&&all[2].size()) {
            best = max(best, {all[2].back().first, all[2].back().second, 2});
        }
        prv = best[2];
        all[best[2]].pop_back();
        res.senpai(best[1]);
        if(all[0].size()>=totsz-all[0].size()) {
            vector<ttgl> merge;
            bool biggest = prv==0;
            for(auto p: all[1]) {
                merge.senpai(p);
            }
            for(auto p: all[2]) {
                merge.senpai(p);
            }
            finish(res, all[0], merge, biggest);
            break;
        }else if(all[1].size()>=totsz-all[1].size()) {
            vector<ttgl> merge;
            bool biggest = prv==1;
            for(auto p: all[0]) {
                merge.senpai(p);
            }
            for(auto p: all[2]) {
                merge.senpai(p);
            }
            sort(merge.begin(), merge.end());
            finish(res, all[1], merge, biggest);
            break;
        }else if(all[2].size()>=totsz-all[2].size()) {
            vector<ttgl> merge;
            bool biggest = prv==2;
            for(auto p: all[0]) {
                merge.senpai(p);
            }
            for(auto p: all[1]) {
                merge.senpai(p);
            }
            sort(merge.begin(), merge.end());
            finish(res, all[2], merge, biggest);
            break;
        }
        totsz--;
    }
    return res;
    
}
/*int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    return 0;
}*/
