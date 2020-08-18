    #include "Alicelib.h"
    #include <bits/stdc++.h>
    using namespace std;
    void Alice(int n, int m, int* a, int* b) 
    {
        vector<pair<int, int>> edges;
        for(int i = 0; i < n; ++i) for(int bit = 0; bit < 10; ++bit)
        {
            if(i & (1 << bit)) 
                edges.push_back(make_pair(i, n + bit));
        }
        
        for(int i = 0; i < 9; ++i) 
        {
            edges.push_back(make_pair(n + i, n + i + 1));
        }
        
        for(int i = 0; i < n + 10; ++i) 
        {
            edges.push_back(make_pair(i, n + 10));
        }
        
        for(int i = 0; i < 10; ++i) 
        {
            edges.push_back(make_pair(n + i, n + 11));
        }
        
        InitG(n + 12, m + edges.size());
        
        for(int i = 0; i < m; ++i) 
        {
            MakeG(i, a[i], b[i]);
        }
     
        for(int i = 0; i < edges.size(); ++i)
        {
            MakeG(i + m, edges[i].first, edges[i].second);
        }
    }
    
    #include "Boblib.h"
    #include <bits/stdc++.h>
    using namespace std;
    void Bob(int v, int u, int* c, int* d) {
        vector<int> adj[1013];
        bool flag[1013];
        int bck[1013];
        memset(bck, 0, sizeof(bck));
        memset(flag, false, sizeof(flag));
        for(int i=0; i<u; ++i) {
            adj[c[i]].push_back(d[i]);
            adj[d[i]].push_back(c[i]);
        }
        int ten = -1;
        for(int i=0; i<v; ++i) {
            //cout<<i<<" "<<adj[i].size()<<"\n";
            if(adj[i].size()==v-2) ten = i;
        }
        for(int u: adj[ten]) {
            flag[u] = true;
        }
        int eleven = -1;
        for(int i=0; i<v; ++i) {
            if(flag[i]||i==ten)continue;
            eleven = i;
        }
        vector<int> special[1013];
        memset(flag, false, sizeof(flag));
        for(int u: adj[eleven]) {
            for(int v: adj[u]) {
                if(flag[v]) {
                    //cout<<u<<" "<<v<<"\n";
                    special[u].push_back(v);
                    special[v].push_back(u);
                }
            }
            flag[u] = true;
        }
        flag[ten] = flag[eleven] = true;
        int curr = -1;
        for(int i=0; i<v; ++i) {
            if(special[i].size()==1) {
                //cout<<i<<"\n";
                if(curr==-1||adj[curr].size()<adj[i].size()) {
                    curr = i;
                }
            }
        }
        int prv = -1;
        for(int i=0; i<10; ++i) {
            //cout<<curr<<" "<<prv<<"\n";
            for(int u: adj[curr]) {
                if(flag[u])continue;
                bck[u]^=1<<i;
            }
            int nxt = -1;
            for(int u: special[curr]) {
                if(u==prv)continue;
                nxt = u;
            }
            prv = curr;
            curr = nxt;
        }
        vector<pair<int, int>> ans;
        for(int i=0; i<u; ++i) {
            if(flag[c[i]]||flag[d[i]]) continue;
            ans.push_back({bck[c[i]], bck[d[i]]});
        }
        InitMap(v-12, ans.size());
        for(auto p: ans) {
            MakeMap(p.first, p.second);
        }
    }
