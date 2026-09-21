// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum

#include<bits/stdc++.h>
using namespace std;

#include"data-structure/segtree.hpp"
#include"tree/heavy-light-decomposition.hpp"

using ll=long long;
ll op(ll a,ll b){return a+b;}
ll e(){return 0;}

int main(){
  int n,q;
  cin>>n>>q;
  vector<ll> a(n);
  for (int i=0;i<n;i++) cin>>a[i];
  HeavyLightDecomposition g(n);
  for (int i=0;i<n-1;i++){
    int u,v;
    cin>>u>>v;
    g.add_edge(u,v);
  }
  g.build();
  vector<ll> v(n);
  for (int i=0;i<n;i++) v[g.in[i]]=a[i];
  SegTree<ll,op,e> seg(v);
  while (q--){
    int t;
    cin>>t;
    if (t==0){
      int p,x;
      cin>>p>>x;
      seg.set(g.in[p],seg.get(g.in[p])+x);
    }
    if (t==1){
      int u,v;
      cin>>u>>v;
      ll ans=0;
      g.path_query(u,v,[&](int l,int r){
        ans+=seg.prod(l,r);
      });
      cout<<ans<<endl;
    }
  }
}
