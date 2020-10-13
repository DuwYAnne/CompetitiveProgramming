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
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>*/
 
using ll = long long;
using ld = long double;
const ll MOD = 998244353;
const ll root = 62;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 100001;
string arr[mxN];
int n, m;
struct node {
    int adj[4];
    vector<int> ind;
}trie[2][20*mxN];
int cnt[2] = {0, 0};
int hsh(char a) {
    if(a=='A')return 0;
    if(a=='C')return 1;
    if(a=='G')return 2;
    if(a=='U')return 3;
    cout<<"REEE\n";
    return 0;
}
void add(string &a, int t, int id) {
    int rt = 0;
    //cout<<a<<"\n";
    for(char c: a) {
        //cout<<rt<<" "<<c<<"\n";
        int k = hsh(c);
        if(trie[t][rt].adj[k]==-1){
            trie[t][rt].adj[k] = ++cnt[t];
        }
        rt = trie[t][rt].adj[k];
        trie[t][rt].ind.senpai(id);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    owo(i, 0, 20*mxN) {
        owo(j, 0, 4) {
            trie[0][i].adj[j] = -1;
            trie[1][i].adj[j] = -1;
        }
    }
    owo(i, 0, n) {
        cin>>arr[i];
    }
    sort(arr, arr + n);
    owo(i, 0, n) {
        add(arr[i], 0, i);
        reverse(arr[i].begin(), arr[i].end());
        add(arr[i], 1, i);
    }
    string p, q;
    owo(i, 0, m) {
        cin>>p>>q;
        reverse(q.begin(), q.end());
        int pid = 0;
        int qid = 0;
        for(char c: p) {
            int nxt = hsh(c);
            if(trie[0][pid].adj[nxt]==-1){
                pid = -1;
                break;
            }
            pid = trie[0][pid].adj[nxt];
        }
        for(char c: q) {
            int nxt = hsh(c);
            if(trie[1][qid].adj[nxt]==-1) {
                qid = -1;
                break;
            }
            qid = trie[1][qid].adj[nxt];
        }
        if(pid==-1||qid==-1)cout<<"0\n";
        else {
            /*for(int k: trie[0][pid].ind) {
                cout<<k<<" ";
            }
            cout<<"\n";
            for(int k: trie[1][qid].ind) {
                cout<<k<<" ";
            }
            cout<<"\n";*/
            int l = trie[0][pid].ind[0];
            int r = trie[0][pid].ind.back();
            vector<int> &k =trie[1][qid].ind;
            int right = lower_bound(k.begin(), k.end(), r + 1) - k.begin();
            int left = lower_bound(k.begin(), k.end(), l) - k.begin();
            cout<<(right - left)<<"\n";
        }
    }
    return 0;
}
