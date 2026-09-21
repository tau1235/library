#pragma once

struct HeavyLightDecomposition{
  int n;
  int root;
  vector<vector<int>> g;
  vector<int> sz,par,dep;
  vector<int> euler,in,out;
  vector<int> head;
  HeavyLightDecomposition(int n,int root=0):n(n),root(root),g(n),sz(n),par(n),dep(n),euler(n),in(n),out(n),head(n){}

  void add_edge(int u,int v){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  void build(){
    auto dfs=[&](auto dfs,int v,int p)-> void {
      sz[v]=1;
      par[v]=p;
      dep[v]=p==-1?0:dep[p]+1;
      if (n!=1&&g[v][0]==p&&(int)g[v].size()>=2) swap(g[v][0],g[v].back());
      for (int &u:g[v]){
        if (u==p) continue;
        dfs(dfs,u,v);
        sz[v]+=sz[u];
        if (sz[g[v][0]]<sz[u]) swap(u,g[v][0]);
      }
    };
    dfs(dfs,root,-1);
    int now=0;
    auto dfs2=[&](auto dfs2,int v,int p)-> void {
      if (v==root) head[v]=v;
      euler[now]=v;
      in[v]=now++;
      for (int u:g[v]){
        if (u==p) continue;
        head[u]=u==g[v][0]?head[v]:u;
        dfs2(dfs2,u,v);
      }
      out[v]=now;
    };
    dfs2(dfs2,root,-1);
  }
  int lca(int u,int v){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    while (true){
      if (in[u]<in[v]) swap(u,v);
      if (head[u]==head[v]) return v;
      u=par[head[u]];
    }
  }
  int dist(int u,int v){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    return dep[u]+dep[v]-dep[lca(u,v)]*2;
  }
  int jump(int v,int k){
    assert(0<=v&&v<n);
    assert(0<=k&&k<=dep[v]);
    while (k){
      if (dep[v]-dep[head[v]]<k){
        k-=dep[v]-dep[par[head[v]]];
        v=par[head[v]];
      }
      else{
        v=euler[in[v]-k];
        k=0;
      }
    }
    return v;
  }
  int jump(int u,int v,int k){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    int l=lca(u,v);
    assert(0<=k&&k<=dep[u]+dep[v]-2*dep[l]);
    if (k<=dep[u]-dep[l]) return jump(u,k);
    return jump(v,dep[u]+dep[v]-2*dep[l]-k);
  }

  vector<pair<int,int>> ascend(int u,int v){
    vector<pair<int,int>> ret;
    while (head[u]!=head[v]){
      ret.push_back({in[u],in[head[u]]});
      u=par[head[u]];
    }
    if (u!=v) ret.push_back({in[u],in[v]+1});
    return ret;
  }
  vector<pair<int,int>> descend(int u,int v){
    if (u==v) return {};
    if (head[u]==head[v]) return {{in[u]+1,in[v]}};
    auto ret=descend(u,par[head[v]]);
    ret.push_back({in[head[v]],in[v]});
    return ret;
  }
  template<typename F>
  void path_query(int u,int v,const F &f,bool vertex=true){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    int l=lca(u,v);
    for (auto [a,b]:ascend(u,l)) f(b,a+1);
    if (vertex) f(in[l],in[l]+1);
    for (auto [a,b]:descend(l,v)) f(a,b+1);
  }
  template<typename F>
  void path_noncommutative_query(int u,int v,const F &f,bool vertex=true){
    assert(0<=u&&u<n);assert(0<=v&&v<n);
    int l=lca(u,v);
    for (auto [a,b]:ascend(u,l)) f(a+1,b);
    if (vertex) f(in[l],in[l]+1);
    for (auto [a,b]:descend(l,v)) f(a,b+1);
  }
};
