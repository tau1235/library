// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
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
    ll l,r,a,b;
    cin>>l>>r>>a>>b;
    lct.add_seg(l,r,a,b);
  }
  while (q--){
    int t;
    cin>>t;
    if (t==0){
      ll l,r,a,b;
      cin>>l>>r>>a>>b;
      lct.add_seg(l,r,a,b);
    }
    if (t==1){
      ll p;
      cin>>p;
      ll ans=lct.query(p);
      if (ans==e()) cout<<"INFINITY\n";
      else cout<<ans<<"\n";
    }
  }
}
