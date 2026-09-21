// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"fps/formal-power-series.hpp"
#include"fps/relaxed-convolution.hpp"

using mint=modint998244353;
using fps=FormalPowerSeries<mint>;

int main(){
  int n,m;
  cin>>n>>m;
  int k=n+m-1;
  vector<int> a(k),b(k);
  for (int i=0;i<n;i++) cin>>a[i];
  for (int i=0;i<m;i++) cin>>b[i];
  RelaxedConvolution<mint> f;
  for (int i=0;i<k;i++) cout<<f.add(a[i],b[i]).val()<<" \n"[i==k-1];
}
