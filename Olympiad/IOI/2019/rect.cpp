#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int mxN = 2501;
int n, m;
int BIT[mxN][mxN];
vector<vector<int>> arr;
vector<int> atrow[mxN][mxN];
vector<pair<int, int>> atcol[mxN];
vector<int> len[mxN];
vector<int> ch[mxN];
void upd(int num, int pos, int del) {
    pos++;
    while(pos < n) {
        BIT[num][pos]+=del;
        pos += pos&-pos;
    }
}
int sum(int num, int pos) {
    int res = 0;
    pos++;
    while(pos) {
        res+=BIT[num][pos];
        pos -= pos&-pos;
    }
}
ll count_rectangles(vector<vector<int>> A) {
    arr = A;
    n = A.size();
    m = A[0].size();
    for(int i = 1; i < n-1; ++i) {
        vector<int> stk;
        for(int j = 0; j < m; ++j) {
            while(stk.size() && arr[i][stk.back()] < arr[i][j])stk.pop_back();
            if(stk.size() && j - stk.back() > 1) {
                atcol[i].emplace_back(stk.back(), j);
            }
            stk.push_back(j);
        }
        stk.clear();
        for(int j = m-1; j >= 0; --j) {
            while(stk.size() && arr[i][stk.back()] < arr[i][j])stk.pop_back();
            if(stk.size() && stk.back() - j > 1) {
                atcol[i].emplace_back(j, stk.back());
            }
            stk.push_back(j);
        }
        sort(atcol[i].begin(), atcol[i].end());
        atcol[i].resize(unique(atcol[i].begin(), atcol[i].end()) - atcol[i].begin());
    }
    for(int j = 1; j < m-1; ++j) {
        vector<int> stk;
        vector<pair<int, int>> ex;
        for(int i = 0; i < n; ++i) {
            while(stk.size() && arr[stk.back()][j] < arr[i][j])stk.pop_back();
            if(stk.size() && i - stk.back() > 1) {
                ex.emplace_back(stk.back(), i);
            }
            stk.push_back(i);
        }
        stk.clear();
        for(int i = n-1; i >= 0; --i) {
            while(stk.size() && arr[stk.back()][j] < arr[i][j])stk.pop_back();
            if(stk.size() && stk.back() - i > 1) {
                ex.emplace_back(i, stk.back());
            }
            stk.push_back(i);
        }
        sort(ex.begin(), ex.end());
        ex.resize(unique(ex.begin(), ex.end()) - ex.begin());
        for(auto p: ex) {
            atrow[p.first][p.second].push_back(j);
        }
    }
    for(int j = m-1; j > 1; --j) {
        len[j].resize(atcol[j].size());
        for(int i = 0; i < atcol[j].size(); ++i) {
            int above = lower_bound(atcol[j+1].begin(), atcol[j+1].end(), atcol[j][i]) - atcol[j+1].begin();
            if(above==atcol[j+1].size() || atcol[j+1][above]!=atcol[j][i]) {
                len[j][i] = 1;
            }else {
                len[j][i] = len[j+1][above] + 1;
            }
        }
    }
    ll res = 0;
    for(int i = 1; i < m-1; ++i) {
        for(int j = i; j < m-1; ++j) {
            ch[j].clear();
        }
        for(int j = 0; j < atcol[i].size(); ++j) {
            upd(atcol[i][j].first, atcol[i][j].second, 1);
            ch[i + len[i][j] - 1].push_back(j);
        }
        for(int j = i; j < m-1; ++j) {
            int prv = 1;
            for(int k = 0; k < atrow[i+1][j-1].size(); ++k) {
                if(k && atrow[i+1][j-1][k-1]==atrow[i+1][j-1][k]-1)prv++;
                else prv = 1;
                res += sum(atrow[i+1][j-1][k] - prv, atrow[i+1][j-1][k] + 1);
            }
            for(int k: ch[j]) {
                upd(atcol[i][k].first, atcol[i][k].second, -1);
            }
        }
    }
    return res;
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    return 0;
}
