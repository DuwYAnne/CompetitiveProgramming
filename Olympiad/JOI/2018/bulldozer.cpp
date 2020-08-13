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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ttgl, null_type,less<ttgl>, rb_tree_tag,tree_order_statistics_node_update>
 
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
const int mxN = 2048;
int n;
//0 = max_prefix; 1 = max_suffix; 2 = realmax; 3 = sum
array<ll, 4> sgmax[2*mxN];
void upd(int p, ll val) {
    sgmax[p+=mxN] = {val, val, val, val};
    while(p>1) {
      p/=2;
      sgmax[p][0] = max(sgmax[2*p][0], sgmax[2*p][3] + sgmax[2*p+1][0]);
      sgmax[p][1] = max(sgmax[2*p+1][1], sgmax[2*p+1][3] + sgmax[2*p][1]);
      sgmax[p][2] = max({sgmax[2*p][2], sgmax[2*p+1][2], sgmax[2*p][1] + sgmax[2*p+1][0]});
      sgmax[p][3] = sgmax[2*p][3] + sgmax[2*p+1][3];
      //cout<<p<<" "<<sgmax[p][0]<<" "<<sgmax[p][1]<<" "<<sgmax[p][2]<<" "<<sgmax[p][3]<<"\n";
    }
}
/*array<ll, 4> qmax(int l, int r) {
    array<ll, 4> left = {0, 0, 0, 0};
    array<ll, 4> right = {0, 0, 0, 0};
    r++;
    for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if(l&1) left = merge(left, sgmax[l++]);
        if(r&1) right = merge(sgmax[--r], right);
    }
    return merge(left, right);
}*/
struct event{
    ll dx;
    ll dy;
    int a, b;
    event(int x1, int y1, int x2, int y2, int aa, int bb) {
        a = aa;
        b = bb;
        int x = x2-x1;
        int y = y2-y1;
        int k = gcd(x, y);
        x/=k;
        y/=k;
        if(x<0||(x==0&&y<0)) {
            x = -x;
            y = -y;
        }
        dx = x;
        dy = y;
        //cout<<x<<" "<<y<<'\n';
    }
    bool operator<(const event &other) const{
        return dx*other.dy > dy*other.dx;
    }
};
vector<event> all;
array<int, 4> arr[mxN];
int ord[mxN];
int lst[mxN];
int dsu[mxN];
int prv[mxN];
int curr;
int find(int a) {
    if(lst[a]!=curr) {
        lst[a] = curr;
        dsu[a] = a;
    }
    return a==dsu[a] ? a : dsu[a] = find(dsu[a]);
}
void merge(int a, int b) {
    dsu[find(a)] = find(b); 
}
bool fix(int a, int b) {
    return ord[a]<ord[b];
}
void swapp(int a, int b) {
    swap(arr[ord[a]], arr[ord[b]]);
    swap(ord[a], ord[b]);
    upd(ord[a], arr[ord[a]][2]);
    upd(ord[b], arr[ord[b]][2]);
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    owo(i, 0, n) {
        cin>>arr[i][0]>>arr[i][1]>>arr[i][2];
        arr[i][3] = i;
    }
    owo(i, 0, n) {
        owo(j, i+1, n) {
            all.senpai(event(arr[i][0], arr[i][1], arr[j][0], arr[j][1], i, j));
            //cout<<arr[i][0]<<" "<<arr[i][1]<<" "<<arr[j][0]<<" "<<arr[j][1]<<" "<<all[all.size()-1].inter<<"\n";
        }
    }
    //ayaya;
    sort(all.begin(), all.end());
    sort(arr, arr+n);
    owo(i, 0, n) {
        upd(i, arr[i][2]);
        ord[arr[i][3]] = i;
    }
    //cout<<qmax(0, n-1)[2]<<"\n";
    ll ans = sgmax[1][2];
    for(int i=0; i<all.size(); ) {
        int j= i+1;
        curr++;
        while(j<all.size()&&all[i].dx==all[j].dx&&all[i].dy==all[j].dy)j++;
        owo(k, i, j) {
            //cout<<all[k].a<<" "<<all[k].b<<endl;
            merge(all[k].a, all[k].b);
        }
        gp_hash_table<int, vector<int>> swp;
        owo(k, i, j) {
            if(prv[all[k].a]!=curr) {
                prv[all[k].a] = curr;
                swp[find(all[k].a)].senpai(all[k].a);
            }
            if(prv[all[k].b]!=curr) {
                prv[all[k].b] = curr;
                swp[find(all[k].b)].senpai(all[k].b);
            }
        }
        for(auto p: swp) {
            sort(p.second.begin(), p.second.end(), fix);
            int left =0;
            int right = p.second.size()-1;
            while(left<right) {
                swapp(p.second[left++], p.second[right--]);
            }
        }
        ans = max(ans, sgmax[1][2]);
        i = j;
    }
    cout<<ans<<"\n";
    return 0;
}
