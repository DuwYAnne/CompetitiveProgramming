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
const ll MOD = 1000000007;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const double PI = acos(-1);
const double eps = -1e6;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
string stuff = "ACGT";
set<string> flag;
map<string, string> best;
void dfs(string s, string ori) {
    if(s.size()>8)return;
    if(flag.count(s))return;
    flag.insert(s);
    //cout<<s<<" "<<ori<<"\n";
    best[s] = ori;
    owo(i, 1, s.size()) {
        if(s[i-1]=='T'&&s[i]=='C') {
            string nxt = s.substr(0, i-1) + "A" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i-1]=='A'&&s[i]=='G') {
            string nxt = s.substr(0, i-1) + "C" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i-1]=='C'&&s[i]=='T') {
            string nxt = s.substr(0, i-1) + "G" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i-1]=='G'&&s[i]=='A') {
            string nxt = s.substr(0, i-1) + "T" + s.substr(i+1);
            dfs(nxt, ori);
        }
    }
    owo(i, 0, s.size()) {
        if(s[i]=='A') {
            string nxt = s.substr(0, i) + "TC" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i]=='C') {
            string nxt = s.substr(0, i) + "AG" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i]=='G') {
            string nxt = s.substr(0, i) + "CT" + s.substr(i+1);
            dfs(nxt, ori);
        }
        if(s[i]=='T') {
            string nxt = s.substr(0, i) + "GA" + s.substr(i+1);
            dfs(nxt, ori);
        }
    }
}
void precomp() {
    owo(msk, 0, 1024) {
        int num = msk;
        string nxt;
        while(num>0) {
            nxt+=stuff[num%4];
            num/=4;
        }
        if(best.find(nxt)==best.end()) {
            flag.clear();
            dfs(nxt, nxt);
        }
    }
}
string getbest(string s) {
    if(s.size()<=5) {
        return best[s];
    }
    string curr = s.substr(0, 4);
    owo(i, 4, s.size()) {
        curr = best[curr+s[i]];
    }
    return best[curr];
}
string type[101];
int n;
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    precomp();
    cin>>n;
    string str;
    owo(i, 0, n) {
        cin>>str;
        type[i] = getbest(str);
        //cout<<str<<" "<<type[i]<<'\n';
    }
    owo(i, 0, n) {
        owo(j, 0, n) {
            if(type[i]==type[j]) {
                cout<<"1";
            }else {
                cout<<"0";
            }
        }
        cout<<"\n";
    }
    return 0;
}
