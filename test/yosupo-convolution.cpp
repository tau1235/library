// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"fps/formal-power-series.hpp"

using mint=modint998244353;
using fps=FormalPowerSeries<mint>;

int main(){
  int n,m;
  cin>>n>>m;
  fps a(n),b(m);
  for (int i=0;i<n;i++) cin>>a[i];
  for (int i=0;i<m;i++) cin>>b[i];
  fps c=a*b;
  for (int i=0;i<n+m-1;i++) cout<<c[i]<<" \n"[i==n+m-2];
}
