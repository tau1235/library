// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min

#include<bits/stdc++.h>
using namespace std;

#include"data-structure/li-chao-tree.hpp"

using ll=long long;
ll inf=5e18;
ll e(){return inf;}

int main(){
  using ll=long long;
  ll inf=5e18;
  int n,q;
  cin>>n>>q;
  vector<ll> xs;
  vector<ll> a(n),b(n);
  for (int i=0;i<n;i++) cin>>a[i]>>b[i];
  vector<tuple<int,ll,ll>> vt(q);
  for (int i=0;i<q;i++){
    int t;
    cin>>t;
    if (t==0){
      ll a,b;
      cin>>a>>b;
      vt[i]={t,a,b};
    }
    if (t==1){
      ll p;
      cin>>p;
      xs.push_back(p);
      vt[i]={t,p,-1};
    }
  }
  LiChaoTree<ll,e> lct(xs);
  for (int i=0;i<n;i++) lct.add(a[i],b[i]);
  for (auto [t,a,b]:vt){
    if (t==0) lct.add(a,b);
    if (t==1){
      ll ans=lct.query(a);
      cout<<ans<<endl;
    }
  }
}
