// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/set_xor_min

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"data-structure/xor-segtree.hpp"

int op(int a,int b){return max(a,b);}
int e(){return 0;}
bool g(int x){return x==0;}

int main(){
  int q;
  cin>>q;
  XorSegmentTree<int,op,e> seg(1<<30);
  while (q--){
    int t,x;
    cin>>t>>x;
    if (t==0) if (seg.get(x)==0) seg.set(x,1);
    if (t==1) if (seg.get(x)!=0) seg.set(x,0);
    if (t==2){
      seg.operate_xor(x);
      cout<<seg.max_right<g>(0)<<"\n";
      seg.operate_xor(x);
    }
  }
}
