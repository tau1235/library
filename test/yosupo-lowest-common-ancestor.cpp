// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"tree/heavy-light-decomposition.hpp"

int main(){
  int n,q;
  cin>>n>>q;
  HeavyLightDecomposition g(n);
  for (int i=0;i<n-1;i++){
    int p;
    cin>>p;
    g.add_edge(i+1,p);
  }
  g.build();
  while (q--){
    int u,v;
    cin>>u>>v;
    cout<<g.lca(u,v)<<"\n";
  }
}
