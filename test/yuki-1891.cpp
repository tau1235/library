// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1891

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"data-structure/xor-segtree-static.hpp"

using mint=modint998244353;
struct S{mint a,b;};
S op(S a,S b){return S{a.a*b.a,b.a*a.b+b.b};}
S e(){return S{1,0};}

int main(){
  int n,q;
  cin>>n>>q;
  vector<S> v(n);
  for (int i=0;i<n;i++) cin>>v[i].a>>v[i].b;
  XorSegmentTreeStatic<S,op,e> seg(v);
  while (q--){
    int l,r,p,x;
    cin>>l>>r>>p>>x;
    seg.operate_xor(p);
    S ret=seg.prod(l,r);
    seg.operate_xor(p);
    mint ans=ret.a*x+ret.b;
    cout<<ans<<"\n";
  }
}
