// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite

#include<bits/stdc++.h>
using namespace std;

#include"modint/modint.hpp"
#include"data-structure/segtree.hpp"
#include"tree/heavy-light-decomposition.hpp"

struct S{mint a,b;};
S op1(S a,S b){return {b.a*a.a,b.a*a.b+b.b};}
S op2(S a,S b){return op1(b,a);}
S e(){return {1,0};}

int main(){
  int n,q;
  cin>>n>>q;
  vector<S> ab(n);
  for (int i=0;i<n;i++){
    int a,b;
    cin>>a>>b;
    ab[i]={a,b};
  }
  HeavyLightDecomposition g(n);
  for (int i=0;i<n-1;i++){
    int u,v;
    cin>>u>>v;
    g.add_edge(u,v);
  }
  g.build();
  vector<S> v(n);
  for (int i=0;i<n;i++) v[g.in[i]]=ab[i];
  SegTree<S,op1,e> seg1(v);
  SegTree<S,op2,e> seg2(v);
  while (q--){
    int t;
    cin>>t;
    if (t==0){
      int p,c,d;
      cin>>p>>c>>d;
      seg1.set(g.in[p],S{c,d});
      seg2.set(g.in[p],S{c,d});
    }
    if (t==1){
      int u,v,x;
      cin>>u>>v>>x;
      S p=e();
      g.path_noncommutative_query(u,v,[&](int l,int r){
        if (l<=r) p=op1(p,seg1.prod(l,r));
        else p=op1(p,seg2.prod(r,l));
      });
      mint ans=p.a*x+p.b;
      cout<<ans.val()<<endl;
    }
  }
}
