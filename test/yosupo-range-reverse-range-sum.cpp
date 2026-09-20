// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_reverse_range_sum

#include<bits/stdc++.h>
using namespace std;

#include"data-structure/splaytree.hpp"

using ll=long long;
ll op(ll a,ll b){return a+b;}
ll e(){return 0;}
ll mapping(ll f,ll x){return x;}
ll composition(ll f,ll g){return 0;}
ll id(){return 0;}

int main(){
  int n,q;
  cin>>n>>q;
  vector<ll> a(n);
  SplayTree<ll,op,e,ll,mapping,composition,id> st;
  for (int i=0;i<n;i++){
    int a;
    cin>>a;
    st.insert(i,a);
  }
  while (q--){
    int t,l,r;
    cin>>t>>l>>r;
    if (t==0) st.reverse(l,r);
    if (t==1){
      ll ans=st.prod(l,r);
      cout<<ans<<endl;
    }
  }
}
