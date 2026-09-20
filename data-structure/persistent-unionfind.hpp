#pragma once

#include"persistent-array.hpp"

struct PersistentUnionFind{
  int n;
  PersistentArray<int,16> par;
  vector<int> nt;
  PersistentUnionFind(int n):n(n),par(vector<int>(n,-1)),nt({0}){}

  int leader_(int t,int v){
    int p=par.get(t,v);
    return p>=0?leader_(t,p):v;
  }
  int leader(int t,int v){return leader_(nt[t],v);}
  int leader(int v){return leader(nt.back(),v);}
  int merge(int t,int u,int v){
    u=leader(t,u);
    v=leader(t,v);
    if (u==v) return u;
    int usz=-par.get(nt[t],u),vsz=-par.get(nt[t],v);
    if (usz<vsz) swap(u,v);
    par.set(nt[t],u,-(usz+vsz));
    par.set(par.prev(),v,u);
    nt.push_back(par.prev());
    return u;
  }
  int merge(int u,int v){return merge(prev(),u,v);}
  bool same(int t,int u,int v){return leader(t,u)==leader(t,v);}
  bool same(int u,int v){return leader(prev(),u)==leader(prev(),v);}
  int size(int t,int v){return -par.get(nt[t],leader(t,v));}
  int size(int v){return -par.get(nt.back(),leader(prev(),v));}
  int prev(){return (int)nt.size()-1;}
};
