#include <bits/stdc++.h>
#include "cmp.h"
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
//write a as power of 4, binary search down and compare at the end;
/*bool stuff[4097][10241];
int idx1 = 0;
int idx2 = 0;
int num;
void bit_set(int a) {
    //cout<<a<<" set\n";
    idx1++;
    stuff[num][a] = true;
}
int bit_get(int a) {
    //cout<<a<<" get\n";
    idx2++;
    return stuff[num][a];
}*/
int sz[7] = {1366, 342, 86, 22, 6, 2, 1};
void remember(int a) {
    int curr = sz[0]+a;
    owo(i, 1, 7) {
        bit_set(curr);
        int diff = (curr-sz[i])/4;
        curr = sz[i+1]+diff;
    }
}
int compare(int b) {
    int pos[7];
    int curr = sz[0]+b;
    owo(i, 1, 8) {
        pos[i-1] = curr;
        if(i<7){
            int diff = (curr-sz[i])/4;
            curr = sz[i+1]+diff;
        }
        //cout<<(i-1)<<" "<<pos[i-1]<<"\n";
    }
    int l = 0;
    int r = 6;
    while(l<r) {
        int mid = (l+r)/2;
        if(mid==6||bit_get(pos[mid])) {
            r = mid;
        }
        else l = mid+1;
    }
    if(l==0)return 0;
    //cout<<l<<" "<<pos[l]<<"\n";
    int add = (pos[l-1]-sz[l-1])/4;
    int diff = (pos[l-1]-sz[l-1])%4;
    //cout<<l<<" "<<pos[l]<<" "<<add<<" "<<diff<<"\n";
    if(diff==0) {
        return -1;
    }else if(diff==3) {
        return 1;
    }else if(diff==1) {
        if(bit_get(sz[l-1]+add*4))return 1;
        else return -1;
    }else {
        if(bit_get(sz[l-1]+3+add*4))return -1;
        else return 1;
    }
}
/*int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    remember(n);
    cout<<compare(m)<<"\n";
    owo(i, 0, 4096) {
        num = i;
        remember(i);
        owo(j, 0, 4096) {
            int k =compare(j);
            if((i==j&&k!=0)||(i>j&&k!=-1)||(i<j&&k!=1)) {
                cout<<"BAD "<<i<<" "<<j<<" "<<k<<"\n";
            }
        }
    }
    return 0;
}
*/
