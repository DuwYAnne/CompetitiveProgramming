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
