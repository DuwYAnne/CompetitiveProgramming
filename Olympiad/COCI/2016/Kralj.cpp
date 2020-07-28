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
const ll MOD = 998244353;
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
const int mxN= 500001;
int n;
int dsu[mxN];
int sz[mxN];
int P[mxN];
int V[mxN];
int arr[mxN];
vector<int> here[mxN];
int find(int a) {
    return a==dsu[a] ? a : dsu[a] = find(dsu[a]);
}
void mergeup(int a) {
    a = find(a);
    sz[a]++;
    int b = find((dsu[a] + sz[a])%n);
    if(a==b)return;
    dsu[b] = a;
    sz[a]+=sz[b];
}
int main() {
    //freopen("xortransform.in", "r", stdin);
    //freopen("xortransform.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        dsu[i] = i;
        sz[i] = 0;
    }
    owo(i, 0, n) {
        cin>>arr[i];
        arr[i]--;
        mergeup(arr[i]);
    }
    owo(i, 0, n) {
        cin>>P[i];
    }
    owo(i, 0, n) {
        cin>>V[i];
    }
    owo(i, 0, n) {
        here[arr[i]].senpai(V[i]);
    }
    int ans =0;
    owo(i, 0, n) {
        if(find(i)==i) {
            multiset<int> elves;
            for(int tt=dsu[i]; tt<dsu[i]+sz[i]; tt++) {
                int j = tt%n;
                for(int k: here[j]) {
                    //cout<<j<<" "<<k<<"\n";
                    elves.insert(k);
                }
                auto it = elves.upper_bound(P[j]);
                if(it!=elves.end()) {
                    elves.erase(it);
                    ans++;
                }else {
                    elves.erase(elves.begin());
                }
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
