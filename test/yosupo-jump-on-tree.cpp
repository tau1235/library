// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"tree/heavy-light-decomposition.hpp"

int main(){
  int n,q;
  cin>>n>>q;
  HeavyLightDecomposition g(n);
  for (int i=0;i<n-1;i++){
    int a,b;
    cin>>a>>b;
    g.add_edge(a,b);
  }
  g.build();
  while (q--){
    int s,t,i;
    cin>>s>>t>>i;
    if (g.dist(s,t)<i) cout<<-1<<"\n";
    else cout<<g.jump(s,t,i)<<"\n";
  }
}
