// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_range_affine_range_sum

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"data-structure/persistent-lazy-segtree.hpp"
#include"modint/modint.hpp"

using ll=long long;

struct S{mint val,siz;};
S op(S a, S b){return S{a.val+b.val,a.siz+b.siz};}
S e(){return S{0,0};}
struct F{mint b,c;};
S mapping(F f,S x){return S{f.b*x.val+f.c*x.siz,x.siz};}
F composition(F f,F g){return F{g.b*f.b,f.b*g.c+f.c};}
F id(){return F{1,0};}

int main(){
  int n,q;
  cin>>n>>q;
  vector<int> a(n);
  vector<S> vec(n);
  for (int i=0;i<n;i++){
    cin>>a[i];
    vec[i]=S{a[i],1};
  }
  PersistentLazySegmentTree<S,op,e,F,mapping,composition,id> seg(vec);
  vector<int> t(q+1,0);
  int now=0;
  for (int i=1;i<=q;i++){
    int type;
    cin>>type;
    if (type==0){
      int k,l,r,b,c;
      cin>>k>>l>>r>>b>>c;
      k++;
      seg.apply(t[k],l,r,F{b,c});
      t[i]=++now;
    }
    if (type==1){
      int k,s,l,r;
      cin>>k>>s>>l>>r;
      k++;s++;
      seg.copy_range(t[k],t[s],l,r);
      t[i]=++now;
    }
    if (type==2){
      int k,l,r;
      cin>>k>>l>>r;
      k++;
      S ans=seg.prod(t[k],l,r);
      cout<<ans.val.val()<<"\n";
    }
  }
  cerr<<seg.pid<<endl;
}
