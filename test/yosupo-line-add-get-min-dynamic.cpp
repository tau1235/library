// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min

#include<bits/stdc++.h>
using namespace std;

#include"data-structure/dynamic-li-chao-tree.hpp"

using ll=long long;
ll inf=5e18;
ll e(){return inf;}

int main(){
  int n,q;
  cin>>n>>q;
  ll lx=-2e9,rx=2e9;
  DynamicLiChaoTree<ll,e> lct(lx,rx);
  for (int i=0;i<n;i++){
    ll a,b;
    cin>>a>>b;
    lct.add(a,b);
  }
  while (q--){
    int t;
    cin>>t;
    if (t==0){
      ll a,b;
      cin>>a>>b;
      lct.add(a,b);
    }
    if (t==1){
      ll p;
      cin>>p;
      cout<<lct.query(p)<<endl;
    }
  }
}
