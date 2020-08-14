//#pragma GCC target ("avx2")
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
ll p10[19];
int arr[mxN];
ll ans = INFLL;
int k;
//after dealing with one digit, we are dealing with n/10 digits the next iteration
void solve(vector<int> all, ll num, int dig, bool seen) {
    if(num>ans)return;
    //cout<<all.size()<<" "<<num<<"\n";
    if(all.size()==1) {
        if(all[0]==0) {
            if(num==0||(seen))num+=p10[dig];
            //cout<<num<<"\n";
            ans = min(ans, num);
            return;
        }
        if(all[0]==1) {
            num+=p10[dig+1];
        }else {
            if(all[0]&1) {
                int k = 0;
                owo(i, 1, 10) {
                    if(all[0]&(1<<i)) {
                        k = i;
                        break;
                    }
                }
                uwu(i, 10, k+1) {
                    if(all[0]&(1<<i))num+=1LL*i*p10[dig++];
                }
                dig++;
                num+=1LL*k*p10[dig];
            }else {
                uwu(i, 10, 1) {
                    if(all[0]&(1<<i)) {
                        num+=1LL*i*p10[dig++];
                    }
                }
            }
        }
        //cout<<num<<"\n";
        ans = min(ans, num);
        return;
    }
    owo(i, 0, 10) {
        vector<int> nxt;
        int curr= i;
        int msk = 0;
        bool ok = false;
        int _ = (1<<10)-1;
        owo(j, 0, all.size()) {
            if(curr==0&&(all[j]&1))ok = true;
            msk|=(all[j]&(_^(1<<curr)));
            curr++;
            if(curr==10) {
                nxt.senpai(msk);
                msk = curr = 0;
            }
        }
        if(curr) {
            nxt.senpai(msk);
        }
        solve(nxt, num+i*p10[dig], dig+1, ok);
    }
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>k;
    owo(i, 0, k) {
        cin>>arr[i];
    }
    vector<int> val;
    p10[0] = 1;
    owo(i, 1, 19) {
        p10[i] = p10[i-1]*10;
    }
    owo(i, 0, k) {
        val.senpai(1<<arr[i]);
    }
    solve(val, 0, 0, 0);
    cout<<ans<<"\n";
    return 0;
}
