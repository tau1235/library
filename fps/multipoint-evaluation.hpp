#pragma once

#include"fps/formal-power-series.hpp"

template<typename mint>
vector<mint> multieval(FormalPowerSeries<mint> f,vector<mint> a){
  using fps=FormalPowerSeries<mint>;
  int m=a.size();
  int sz=1;
  while (sz<m) sz*=2;
  vector<fps> ptree(sz*2,{1});
  for (int i=0;i<m;i++) ptree[sz+i]={-a[i],1};
  for (int i=sz-1;i>=1;i--) ptree[i]=ptree[i*2]*ptree[i*2+1];
  ptree[0]=f;
  for (int i=1;i<sz+m;i++) ptree[i]=ptree[i/2]%ptree[i];
  vector<mint> ret(m);
  for (int i=0;i<m;i++){
    if (ptree[sz+i].empty()) ret[i]=0;
    else ret[i]=ptree[sz+i][0];
  }
  return ret;
}
