// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"data-structure/persistent-lazy-segtree.hpp"

int op(int a,int b){return a+b;}
int e(){return 0;}
int mapping(int f,int x){return x;}
int composition(int f,int g){return f;}
int id(){return 0;}
int b;
bool g(int x,int y){return y-x<=b;}

int main(){
  int m=1e9+10;
  int n,q;
  cin>>n>>q;
  PersistentLazySegmentTree<int,op,e,int,mapping,composition,id,(int)2e7> seg(m);
  vector<int> a(n);
  for (int i=0;i<n;i++){
    cin>>a[i];
    seg.set(a[i],seg.get(a[i])+1);
  }
  while (q--){
    int l,r,k;
    cin>>l>>r>>k;
    b=k;
    int ans=seg.max_right_pair<g>(l,r,0);
    cout<<ans<<"\n";
  }
  cerr<<seg.pid<<endl;
}
