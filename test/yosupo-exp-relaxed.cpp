// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/exp_of_formal_power_series

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"fps/formal-power-series.hpp"
#include"fps/relaxed-exp.hpp"

using mint=modint998244353;
using fps=FormalPowerSeries<mint>;

int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  RelaxedExp<mint> f;
  for (int i=0;i<n;i++){
    cin>>a[i];
    cout<<f.add(a[i]).val()<<" \n"[i==n-1];
  }
}
