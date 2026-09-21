// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"data-structure/persistent-unionfind.hpp"

int main(){
  int n,q;
  cin>>n>>q;
  vector<int> t(q+1);
  PersistentUnionFind uf(n);
  for (int i=0;i<q;i++){
    int type,k,u,v;
    cin>>type>>k>>u>>v;
    k++;
    if (type==0){
      uf.merge(t[k],u,v);
      t[i+1]=uf.prev();
    }
    if (type==1){
      if (uf.same(t[k],u,v)) cout<<1<<"\n";
      else cout<<0<<"\n";
    }
  }
}