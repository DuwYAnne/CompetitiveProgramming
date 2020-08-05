/*#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")*/
#include "messy.h"
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
int ans[128];
int n;
/*set<string> stt;
int nn;
int perm[128];
void add_element(string k) {
    stt.insert(k);
}
bool check_element(string k) {
    return stt.count(k)>0;
}
void compile_set() {
    set<string> nxt;
    for(auto p: stt) {
        string k = p;
        owo(i, 0, n) {
            k[i] = p[perm[i]];
        }
        nxt.insert(k);
    }
    stt.clear();
    for(auto p: nxt) {
        stt.insert(p);
    }
}*/
void place(int l, int r) {
    if(r-l<1)return;
    string s;
    owo(i, 0, n) {
        if(i>=l&&i<=r) {
            s+='1';
        }else {
            s+='0';
        }
    }
    int mid = (l+r)/2;
    owo(i, l, mid+1) {
        s[i] = '0';
        add_element(s);
        s[i] = '1';
    }
    place(l, mid);
    place(mid+1, r);
}
void solve(int l, int r, vector<int> &in) {
    if(r-l<1) {
        ans[l] = in[0];
        return;
    }
    /*cout<<l<<" "<<r<<"\n";
    owo(i, l, r+1) {
        cout<<ans[i]<<" ";
    }
    cout<<"\n";*/
    string s;
    owo(i, 0, n) {
        s+='0';
    }
    for(int i:in) {
        s[i] = '1';
    }
    int mid = (l+r)/2;
    vector<int> right;
    vector<int> left;
    for(int i: in){
        s[i] = '0';
        if(check_element(s)) {
            left.senpai(i);
        }else {
            right.senpai(i);
        }
        s[i] = '1';
    }
    solve(l, mid, left);
    solve(mid+1, r, right);
}
vector<int> restore_permutation(int N, int w, int r) {
    n = N;
    owo(i, 0, n) {
        ans[i] = i;
    }
    vector<int> pass(n);
    owo(i, 0, n) {
        pass[i] = i;
    }
    place(0, n-1);
    compile_set();
    solve(0, n-1, pass);
    vector<int> result(n);
    owo(i, 0, n) {
        result[ans[i]] = i;
    }
    return result;
}
/*int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>nn;
    owo(i, 0, nn) {
        cin>>perm[i];
    }
    vector<int> res = restore_permutation(nn, 0, 0);
    owo(i, 0, nn) {
        cout<<res[i]<<" ";
    }
    return 0;
}*/
