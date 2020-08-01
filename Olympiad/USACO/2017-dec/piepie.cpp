#include <bits/stdc++.h>
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
const int mxN = 100001;
int n, d;
vector<int> adj[2*mxN];
ttgl arr[2*mxN];
int ans[2*mxN];
multiset<ttgl> AA;
multiset<ttgl> BB;
queue<int> Q;
int main() {
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>d;
    memset(ans, -1, sizeof(ans));
    owo(i, 0, 2*n) {
        cin>>arr[i].first>>arr[i].second;
    }
    owo(i, 0, n) {
        if(arr[i].second==0) {
            ans[i] = 1;
            Q.push(i);
        }else {
            AA.insert({arr[i].second, i});
        }
    }
    owo(i, n, 2*n) {
        if(arr[i].first==0) {
            ans[i] = 1;
            Q.push(i);
        }else {
            BB.insert({arr[i].first, i});
        }
    }
    while(!Q.empty()) {
        int curr = Q.front();
        //cout<<curr<<"\n";
        Q.pop();
        if(curr<n) {
            int val = arr[curr].first;
            while(1) {
                auto it = BB.lower_bound({val+1, 0});
                if(it==BB.begin())break;
                it--;
                //cout<<val<<" "<<it->first<<" "<<it->second<<endl;
                if(it->first+d<val)break;
                ans[it->second] = ans[curr]+1;
                Q.push(it->second);
                BB.erase(it);
            }
        }else {
            int val = arr[curr].second;
            while(1) {
                auto it = AA.lower_bound({val+1, 0});
                if(it==AA.begin())break;
                it--;
                //cout<<val<<" "<<it->first<<" "<<it->second<<endl;
                if(it->first+d<val)break;
                ans[it->second] = ans[curr]+1;
                Q.push(it->second);
                AA.erase(it);
            }
        }
    }
    owo(i, 0, n) {
        cout<<ans[i]<<"\n";
    }
    return 0;
}
