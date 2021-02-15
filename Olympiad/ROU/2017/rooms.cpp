/*same as editorial

For each initial component, mark a special spot for the entire room, then on query, do a simple prefix sum to count some of the rooms contained.
All other rooms must have at least one spot on the boundary, so iterate through the boundary and maintain the other id's in some set.
*/

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
using ll = long long;
using ld = long double;
ll MOD = 1000000007;
const ll root = 3;
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const int mxN = 2001;
int n, m, q;
int psum[mxN][mxN];
pair<int, int> ids[mxN*mxN];
int id[mxN][mxN];
int arr[mxN][mxN];
int cnt= 0;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool inside(int a, int b) {
    return a>=0 && a<n && b>=0 && b<m;
}
int get(int a, int b, int c, int d) {
    int res = psum[c][d];
    if(a > 0)res -= psum[a-1][d];
    if(b > 0)res -= psum[c][b-1];
    if(a > 0 && b > 0)res += psum[a-1][b-1];
    return res;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    owo(i, 0, n) {
        string s;
        cin>>s;
        owo(j, 0, m) {
            arr[i][j] = s[j] - 'a';
        }
    }
    memset(id, -1, sizeof(id));
    owo(i, 0, n) {
        owo(j, 0, m) {
            if(id[i][j]==-1) {
                queue<ttgl> Q;
                Q.push({i, j});
                psum[i][j]++;
                ids[cnt] = {i, j};
                id[i][j] = cnt;
                while(!Q.empty()) {
                    int x = Q.front().first;
                    int y = Q.front().second;
                    Q.pop();
                    owo(d, 0, 4) {
                        if(inside(x+dx[d], y+dy[d]) && id[x+dx[d]][y+dy[d]]==-1 && arr[x+dx[d]][y+dy[d]] == arr[x][y]) {
                            id[x+dx[d]][y+dy[d]] = cnt;
                            Q.push({x+dx[d], y+dy[d]});
                        }
                    }
                }
                cnt++;
            }
        }
    }
    owo(i, 0, n) {
        owo(j, 0, m) {
            psum[i][j] += (i>0 && j>0 ? -psum[i-1][j-1] : 0) + (i>0 ? psum[i-1][j] : 0) + (j>0 ? psum[i][j-1] : 0);
            //cout<<i<<" "<<j<<" "<<psum[i][j]<<"\n";
        }
    }
    cin>>q;
    int x1, y1, x2, y2;
    owo(i, 0, q) {
        cin>>x1>>y1>>x2>>y2;
        x1--; y1--; x2--; y2--;
        int ans = get(x1, y1, x2, y2);
        //cout<<ans<<"\n";
        set<int> o;
        owo(j, y1, y2+1) {
            if(o.count(id[x1][j]) > 0)continue;
            int x = ids[id[x1][j]].first;
            int y = ids[id[x1][j]].second;
            if(!(x >= x1 && x <= x2 && y >= y1 && y <= y2))o.insert(id[x1][j]); 
        }
        owo(j, y1, y2+1) {
            if(o.count(id[x2][j]) > 0)continue;
            int x = ids[id[x2][j]].first;
            int y = ids[id[x2][j]].second;
            if(!(x >= x1 && x <= x2 && y >= y1 && y <= y2))o.insert(id[x2][j]);
        }
        owo(j, x1, x2+1) {
            if(o.count(id[j][y1]) > 0)continue;
            int x = ids[id[j][y1]].first;
            int y = ids[id[j][y1]].second;
            if(!(x >= x1 && x <= x2 && y >= y1 && y <= y2))o.insert(id[j][y1]); 
        }
        owo(j, x1, x2+1) {
            if(o.count(id[j][y2]) > 0)continue;
            int x = ids[id[j][y2]].first;
            int y = ids[id[j][y2]].second;
            if(!(x >= x1 && x <= x2 && y >= y1 && y <= y2))o.insert(id[j][y2]);
        }
        cout<<(ans + (int)o.size())<<"\n";
    }
    return 0;
}
