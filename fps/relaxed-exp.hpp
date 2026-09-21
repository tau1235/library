#pragma once

#include"fps/relaxed-convolution.hpp"

template<typename mint>
struct RelaxedExp{
  using fps=FormalPowerSeries<mint>;
  fps g;
  RelaxedConvolution<mint> f;
  int n;
  RelaxedExp(){n=0;}
  const mint operator[](int i)const{return g[i];}
  mint add(mint x){
    if (n==0){
      n++;
      g.push_back(1);
      return g[0];
    }
    else{
      g.push_back(f.add(x*n,g[n-1])*mint(n).inv());
      return g[n++];
    }
  }
};
