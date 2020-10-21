//#pragma GCC target ("avx2")
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
const ll MOD = 1000000007;
const ll root = 62;
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = atan(1);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 1000003;
int arr[mxN];
int cnt[mxN];
vector<int> ind[mxN];
vector<int> ans;
int res;
priority_queue<ttgl> pq;
int n, s;

int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>s;
    owo(i, 0, n) {
        cin>>arr[i];
        arr[i]++;
        arr[i]%=s;
        cnt[arr[i]]++;
        ind[arr[i]].senpai(i);
    }
    owo(i, 1, s) {
        if(cnt[i]) {
            pq.push({cnt[i], i});
        }
    }
    for(int k: ind[0]) {
        ans.senpai(k);
    }
    int curr = 0;
    while(!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        if(curr + p.second == s-1) {
            if(!pq.empty()) {
                auto q = pq.top();
                pq.pop();
                curr+=q.second;
                ans.senpai(ind[q.second].back());
                ind[q.second].pop_back();
                if(q.first > 1) {
                    pq.push({q.first-1, q.second});
                }
                pq.push(p);
            }else {
                curr+=p.second;
                ans.senpai(ind[p.second].back());
                ind[p.second].pop_back();
                if(p.first > 1) {
                    pq.push({p.first-1, p.second});
                }
            }
        }else {
            curr+=p.second;
            ans.senpai(ind[p.second].back());
            ind[p.second].pop_back();
            if(p.first > 1) {
                pq.push({p.first-1, p.second});
            }
        }
        curr%=s;
        if(!pq.empty() && curr == s-1) {
            curr = 0;
            res++;
        }
    }
    cout<<res<<"\n";
    owo(i, 0, n) {
        cout<<(ans[i]+1)<<" ";
    }
    return 0;
}
