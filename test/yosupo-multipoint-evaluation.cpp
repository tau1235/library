// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multipoint_evaluation

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"modint/modint.hpp"
#include"fps/formal-power-series.hpp"
#include"fps/multipoint-evaluation.hpp"

using mint=modint998244353;
using fps=FormalPowerSeries<mint>;

int main(){
  int n,m;
  cin>>n>>m;
  fps c(n),p(m);
  for (int i=0;i<n;i++) cin>>c[i];
  for (int i=0;i<m;i++) cin>>p[i];
  auto ans=multieval(c,p);
  for (int i=0;i<m;i++) cout<<ans[i]<<" \n"[i==m-1];
}
