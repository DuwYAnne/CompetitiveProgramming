#include <bits/stdc++.h>
#include "vision.h"
#define owo(i,a, b) for(int i=(a);i<(b); ++i)
#define uwu(i,a, b) for(int i=(a)-1; i>=(b); --i)
#define senpai push_back
#define ttgl pair<int, int>
#define ayaya cout<<"ayaya~"<<endl
 
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gpu_hash_map<int, int> mp;*/
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
int h, w, k;
int cnt, nxt;
/*int tt = 0;
int arr[1000001];
void add_not(int a){
    arr[nxt++] = arr[a]^1;
}
void add_or(vector<int> a){
    int nw = 0;
    for(int p: a) {
        nw|=arr[p];
    }
    arr[nxt++] = nw;
}
void add_and(vector<int> a){
    int nw = 1;
    for(int p: a) {
        nw&=arr[p];
    }
    arr[nxt++] = nw;
}
void add_xor(vector<int> a){
    int nw = 0;
    for(int p: a) {
        nw^=arr[p];
    }
    arr[nxt++] = nw;
}*/
int _add_not(int a) {add_not(a);return cnt++;}
int _add_or(vector<int> a) {add_or(a);return cnt++;}
int _add_and(vector<int> a) {add_and(a);return cnt++;}
int _add_xor(vector<int> a) {add_xor(a);return cnt++;}
int val(int x, int y) {
    return x*w + y;
}
int solve(int d) {
    //query for all up diagonals
    vector<int> qq;
    vector<int> up;
    vector<int> down;
    owo(i, 0, h) {
        qq.clear();
        owo(j, 0, min(i+1, w)) {
            qq.senpai(val(i-j, j));
        }
        up.senpai(_add_and({_add_or(qq), _add_xor(qq)}));
    }
    owo(i, 1, w) {
        qq.clear();
        owo(j, 0, min(h, w-i)) {
            qq.senpai(val(h-j-1, i+j));
        }
        up.senpai(_add_and({_add_or(qq), _add_xor(qq)}));
    }
    //query for down diagonals
    uwu(i, h, 0) {
        qq.clear();
        owo(j, 0, min(h-i, w)) {
            qq.senpai(val(i+j, j));
        }
        down.senpai(_add_and({_add_or(qq), _add_xor(qq)}));
    }
    owo(i, 1, w) {
        qq.clear();
        owo(j, 0, min(h, w-i)) {
            qq.senpai(val(j, i+j));
        }
        down.senpai(_add_and({_add_or(qq), _add_xor(qq)}));
    }
    vector<int> preup;
    owo(i, 0, up.size()) {
        if(i==0)preup.senpai(_add_xor({up[i]}));
        else {
            preup.senpai(_add_xor({up[i], preup[i-1]}));
        }
    }
    vector<int> predown;
    owo(i, 0, down.size()) {
        if(i==0)predown.senpai(_add_xor({down[i]}));
        else {
            predown.senpai(_add_xor({down[i], predown[i-1]}));
        }
    }
    int upval = 0;
    int downval = 0;
    owo(i, 0, preup.size()-d) {
        qq.clear();
        owo(j, i, i+d) {
            qq.senpai(preup[j]);
        }
        if(i==0) {
            upval = _add_or({_add_and(qq)});
        }else {
            upval = _add_or({upval, _add_and(qq)});
        }
    }
    owo(i, 0, predown.size()-d) {
        qq.clear();
        owo(j, i, i+d) {
            qq.senpai(predown[j]);
        }
        if(i==0) {
            downval = _add_or({_add_and(qq)});
        }else {
            downval = _add_or({downval, _add_and(qq)});
        }
    }
    return _add_or({upval, downval});
}
void construct_network(int H, int W, int K) {
    h = H;
    w = W;
    k = K;
    cnt = h*w;
    nxt = h*w;
    if(w+h-2==k) {
        solve(k);
    }
    else _add_and({solve(k), _add_not(solve(k+1))});
}
/*int n, m, f;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>f;
    owo(i, 0, n) {
        owo(j, 0, m) {
            cin>>arr[i*m+j];
        }
    }
    construct_network(n, m, f);
    cout<<(arr[--nxt])<<"\n";
    return 0;
}*/
