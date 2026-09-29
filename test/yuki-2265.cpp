// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2265

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"data-structure/xor-segtree-noncommutative.hpp"

using mint=modint998244353;
struct S{mint val,pw1,pw2;};
S op(S a,S b){return S{a.val*b.pw1+b.val*a.pw2,a.pw1*b.pw1,a.pw2*b.pw2};}
S e(){return S{0,1,1};}

int main(){
  int n,q;
  string s;
  cin>>n>>s>>q;
  vector<S> v(1<<n);
  for (int i=0;i<1<<n;i++) v[i]=S{s[i]-'0',11,2};
  XorSegmentTreeNonCommutative<S,op,e> seg(v);
  while (q--){
    int t;
    cin>>t;
    if (t==1){
      int x,y;
      cin>>x>>y;
      seg.set(x,S{y,1});
    }
    if (t==2){
      int l,r,x;
      cin>>l>>r>>x;
      r++;
      seg.operate_xor(x);
      cout<<seg.prod(l,r).val<<"\n";
      seg.operate_xor(x);
    }
  }
}
