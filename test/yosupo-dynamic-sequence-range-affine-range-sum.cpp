// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"data-structure/splaytree.hpp"

struct S{
  mint val;
  mint sz;
};
S op(S a,S b){return {a.val+b.val,a.sz+b.sz};}
S e(){return {0,0};}
struct F{mint b,c;};
S mapping(F f,S x){return {x.val*f.b+x.sz*f.c,x.sz};}
F composition(F f,F g){return {f.b*g.b,f.b*g.c+f.c};}
F id(){return {1,0};}

int main(){
  int n,q;
  cin>>n>>q;
  vector<S> v(n);
  for (int i=0;i<n;i++){
    int a;
    cin>>a;
    v[i]={a,1};
  }
  SplayTree<S,op,e,F,mapping,composition,id> st(v);
  while (q--){
    int t;
    cin>>t;
    if (t==0){
      int i,x;
      cin>>i>>x;
      st.insert(i,{x,1});
    }
    if (t==1){
      int i;
      cin>>i;
      st.erase(i);
    }
    if (t==2){
      int l,r;
      cin>>l>>r;
      st.reverse(l,r);
    }
    if (t==3){
      int l,r,b,c;
      cin>>l>>r>>b>>c;
      st.apply(l,r,{b,c});
    }
    if (t==4){
      int l,r;
      cin>>l>>r;
      mint ans=st.prod(l,r).val;
      cout<<ans.val()<<"\n";
    }
  }
}
