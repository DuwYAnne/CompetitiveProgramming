//submitted on atcoder
#include <bits/stdc++.h>
#include "navigation_lib.h"
using namespace std;
vector<int> adj[100001];
int lab[100001];
/*void Flag(int a, int b){};
void Answer(int a) {
  cout<<a<<"\n";
}*/
void dfs(int u, int p=-1) {
  if(p!=-1) {
    if(u<p) {
      lab[u] = lab[p];
    }else {
      lab[u] = lab[p]^1;
    }
    Flag(u, lab[u]);
  }
  for(int v: adj[u]) {
    if(v^p) {
      dfs(v, u);
    }
  }
}
void Anna(int k, int n, int T, int* a, int* b) {
  Flag(T, 0);
  lab[T] = 0;
  for(int i=0; i<n; ++i) {
    adj[a[i]].push_back(b[i]);
    adj[b[i]].push_back(a[i]);
  }
  dfs(T);
}
void Bruno(int k, int s, int f, int l, int* p, int *q) {
  for(int i=0; i<l; ++i) {
    //cout<<f<<" "<<q[i]<<" "<<p[i]<<"\n";
    if((f+q[i]+(p[i]>s))&1) {
      Answer(p[i]);
      return;
    }
  }
  Answer(s);
}
/*int A[100001];
int B[100001];
int N;
int S;
int Q;
int main()
{
  freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
  cin>>N>>S>>Q;
  for(int i=0; i<N-1; ++i) {
    cin>>A[i]>>B[i];
  }
  Anna(0, N, S, A, B);
  int a;
  while(Q--) {
    cin>>a;
    int P[adj[a].size()];
    int qq[adj[a].size()];
    for(int i=0; i<adj[a].size(); ++i) {
      P[i] = adj[a][i];
      qq[i] = lab[adj[a][i]];
    }
    int ll = adj[a].size();
    Bruno(0, a, lab[a], adj[a].size(), P, qq);
  }
}*/
