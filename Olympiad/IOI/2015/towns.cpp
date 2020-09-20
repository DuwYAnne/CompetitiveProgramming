#include "towns.h"
#include <bits/stdc++.h>
         
using namespace std;
         
const int mxN = 111;
int arr[mxN];
int dist[mxN][mxN];
int numHub = 0;
int lcadist[mxN];
int n;
int s, t;
int getdist(int a, int b) {
    if(a==b)return 0;
    if(dist[a][b]==-1) {
        return dist[a][b] = dist[b][a] = getDistance(a, b);
    }
    return dist[a][b];
}
bool solve(int hub) {
    vector<int> stk;
    vector<int> bkt;
    stk.push_back(0);
    function<bool(int, int)> compare = [&](int a, int b) {
        if(lcadist[a] < lcadist[hub] && lcadist[b] < lcadist[hub]) {
            return true;
        }else if(lcadist[a] > lcadist[hub] && lcadist[b] > lcadist[hub]) {
            return true;   
        }else if(lcadist[a] == lcadist[hub] && lcadist[b] == lcadist[hub]) {
            if(getdist(s, a) + getdist(s, b) - getdist(a, b) > 2 * lcadist[hub])return true;
        }
        return false;
    };
    for(int i = 1; i < n; ++i) {
        if(compare(stk.back(), i)) {
            bkt.push_back(i);
        }else {
            stk.push_back(i);
            if(bkt.size()) {
                 stk.push_back(bkt.back());
                bkt.pop_back();
            }
        }
    }
    int T = stk.back();
    while(stk.size()) {
        int lst = stk.back();
        stk.pop_back();
        if(compare(lst, T)) {
            if(stk.size()==0) {
                bkt.push_back(lst);
            }else {
                stk.pop_back();
            }
        }else {
            if(bkt.size()==0) {
                return true;
            }
            bkt.pop_back();
        }
    }
    if(bkt.size())return false;
    return true;
}
int hubDistance(int N, int sub) {
    n = N;
    memset(dist, -1, sizeof(dist));
    for(int i = 1, mxdist = 0; i < n; ++i) {
        if(getdist(0, i) > mxdist) {
            mxdist = getdist(0, i);
            s = i;
        }
    }
    for(int i = 0, mxdist = 0; i < n; ++i) {
        if(i^s) {
            if(getdist(s, i) > mxdist) {
                mxdist = getdist(s, i);
                t = i;
            }
        }
    }
    int hub[2];
    int hubcnt = 0;
    int R = 0x3f3f3f3f;
    for(int i = 0; i < n; ++i) {
        lcadist[i] = (getdist(s, i) + getdist(s, 0) - getdist(i, 0)) / 2;
        if(max(lcadist[i], getdist(s, t) - lcadist[i]) < R) {
            R = max(lcadist[i], getdist(s, t) - lcadist[i]);
            hubcnt = 1;
            hub[0] = i;
        }else if(max(lcadist[i], getdist(s, t) - lcadist[i]) == R && lcadist[i]^lcadist[hub[0]]){
            hubcnt = 2;
            hub[1] = i;
        }
    }
    //cout<<hubcnt<<"\n";
    if(sub <= 2) {
        return R;
    }
    bool balanced = false;
    for(int i = 0; i < hubcnt; ++i) {
        balanced |= solve(hub[i]);
    }
    return (balanced ? 1 : -1) * R;
}
