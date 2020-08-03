#include <bits/stdc++.h>
#include "grader.h"
#include "encoder.h"
using namespace std;
void encode(int n, int h, int m, int *a, int *b) {
    int dist[1001][1001];
    int par[1001][1001];
    vector<int> adj[1001];
    for(int i=0; i<m; ++i) {
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }
    memset(dist, 0x3f3f3f3f, sizeof(dist));
    for(int i=0; i<h; ++i) {
        dist[i][i] = 0;
        queue<int> Q;
        Q.push(i);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int v:adj[u]) {
                if(dist[i][v]!=0x3f3f3f3f)continue;
                dist[i][v] = dist[i][u]+1;
                par[v][i] = u;
                Q.push(v);
            }
        }
    }
    for(int i=1; i<n; ++i) {
        for(int bit=0; bit<10; ++bit) {
            if(par[i][0]&(1<<bit))encode_bit(1);
            else encode_bit(0);
        }
    }
    pair<int, int> info = {0, 0};
    for(int i=1; i<h; ++i) {
        for(int j=1; j<n; ++j) {
            int type = dist[i][j] - dist[i][par[j][0]] + 1;
            info.second++;
            info.first = info.first*3+type;
            if(info.second==3) {
                for(int bit=0; bit<5; ++bit) {
                    if(info.first&(1<<bit))encode_bit(1);
                    else encode_bit(0);
                }
                info.first = 0;
                info.second = 0;
            }
        }
    }
    if(info.second>0) {
        for(int bit=0; bit<5; ++bit) {
            if(info.first&(1<<bit))encode_bit(1);
            else encode_bit(0);
        }
    }
}


//-----------------------------------------------------------------


#include <bits/stdc++.h>
#include "grader.h"
#include "decoder.h"
using namespace std;
void decode(int n, int h) {
    int change[1001][1001];
    int dist[1001];
    vector<int> adj[1001];
    memset(change, 0, sizeof(change));
    memset(dist, 0, sizeof(dist));
    for(int i=1; i<n; ++i) {
        int p = 0;
        for(int bit=0; bit<10; ++bit) {
            if(decode_bit())p+=1<<bit;
        }
        adj[p].push_back(i);
        change[0][i] = 1;
    }
    function<void(int, int, int)>dfs = [&](int hub, int u, int p) 
    {
        for(int v: adj[u]) {
            if(v^p) {
                dist[v] = dist[u] + change[hub][v];
                dfs(hub, v, u);
            }
        }
    };
    int info = 0;
    for(int i=1; i<h; ++i) {
        for(int j=1; j <n; ++j) {
            info++;
            if(info==3) {
                int num = 0;
                for(int bit=0; bit<5; ++bit) {
                    if(decode_bit())num+=1<<bit;
                }
                int k1 = i;
                int k2 = j;
                for(int nn=0; nn<3; ++nn) {
                    change[k1][k2] = (num%3)-1;
                    num/=3;
                    k2--;
                    if(k2==0) {
                        k2 = n-1;
                        k1--;
                    }
                }
                info = 0;
            }
        }
    }
    if(info>0) {
        int num = 0;
        for(int bit=0; bit<5; ++bit) {
            if(decode_bit())num+=1<<bit;
        }
        int k1 = h-1;
        int k2 = n-1;
        for(int nn=0; nn<info; ++nn) {
            change[k1][k2] = (num%3)-1;
            num/=3;
            k2--;
            if(k2==0) {
                k2 = n-1;
                k1--;
            }
        }
        info = 0;
    }
    for(int i=0; i<h; ++i) {
        dfs(i, 0, 0);
        for(int j=0; j<n; ++j) {
            hops(i, j, dist[j]-dist[i]);
        }
    }
}
