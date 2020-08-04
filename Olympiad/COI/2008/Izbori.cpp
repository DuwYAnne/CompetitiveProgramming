//--------------------------------------------------------------------NOT SUBMITTED-------------------------------------------------------------------
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
const int mxN = 101;
int arr[mxN];
int farr[mxN];
ttgl srt[mxN];
ttgl ans[mxN];
int num[mxN];
int gt[mxN];
int v, nn, n, m;
int req;
void computemax(int idx) {
    memset(num, 0, sizeof(num));
    arr[idx]+=req;
    if(arr[idx]*20<v) {
        arr[idx]-=req;
        return;
    }
    owo(bb, 0, m) {
        array<int, 3> best = {0, 1, 0};
        owo(i, 0, nn) {
            if(arr[i]*20<v)return;
            if(best[1]*arr[i]>best[0]*(num[i]+1)) {
                best = {arr[i], num[i]+1, i};
            }
        }
        num[best[2]]++;
    }
    ans[idx].first = num[idx];
    arr[idx]-=req;
}
void computemin(int idx) {
    //if we fix the number of seats some guy gets, we can assign votes to everyone else to minimize with dp
    //lets compute dp[i][j] = min assigned to have i win j seats :
    // transition is dp[i][j] = min(k<j dp[i-1][k] + cost to win j-k seats)
    //kinda weird because fractions :/
    if(farr[idx]*20<v)return;
    int dp[mxN][2*mxN];
    int l = 0;
    int r = m;
    while(l<r) {
        int mid = (l+r)/2;
        memset(dp, INF, sizeof(dp));
        dp[0][0] = 0;
        ttgl smal = {farr[idx], mid+1};
        owo(i, 1, n+1) {
            if(i==idx+1) {
                owo(j, 0, m+1) {
                    dp[i][j] = dp[i-1][j];
                }
                continue;
            }
            owo(j, 0, m+1) {
                owo(k, 0, j+1) {
                    int cost = 0;
                    int w = j-k;
                    if(gt[i-1]<gt[idx]) {
                        if((w*smal.first)%smal.second==0) {
                            cost = (w*smal.first)/smal.second;
                        }else {
                            cost = (w*smal.first)/smal.second+1;
                        }
                    }else {
                        cost = (w*smal.first)/smal.second+1;
                    }
                    cost = max(0, cost-farr[i-1]);
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + cost);
                }
            }
        }
        //cout<<gt[idx]<<" "<<mid<<" "<<dp[n][m-mid]<<"\n";
        if(dp[n][m-mid]<=req)r = mid;
        else l = mid+1;
    }
    ans[gt[idx]].second = l;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>v>>nn>>m;
    req = v;
    owo(i, 0, nn) {
        cin>>arr[i];
        req-=arr[i];
        srt[i] = {arr[i], i};
    }
    sort(srt, srt+nn);
    reverse(srt, srt+nn);
    owo(i, 0, min(20, nn)){
        gt[n] = srt[i].second;
        farr[n++] = srt[i].first;
    }
    //simulate max :/
    owo(i, 0, nn) {
        computemax(i);
    }
    //binary search on min
    owo(i, 0, n) {
        computemin(i);
    }
    owo(i, 0, nn) {
        cout<<ans[i].first<<" ";
    }
    cout<<"\n";
    owo(i, 0, nn) {
        cout<<ans[i].second<<" ";
    }
    return 0;
}
