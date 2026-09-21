// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"fps/formal-power-series.hpp"

using mint=modint998244353;
using fps=FormalPowerSeries<mint>;

int main(){
  int n;
  cin>>n;
  fps a(n);
  for (int i=0;i<n;i++) cin>>a[i];
  fps b=a.inv();
  for (int i=0;i<n;i++) cout<<b[i]<<" \n"[i==n-1];
}
