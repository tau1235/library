#pragma once

#include"fps/formal-power-series.hpp"

template<typename mint>
struct RelaxedConvolution{
  using fps=FormalPowerSeries<mint>;
  fps f,g,h;
  int n;
  vector<fps> vf,vg;
  RelaxedConvolution(){n=0;};
  const mint operator[](int i)const{return h[i];}
  mint add(mint x,mint y){
    h.resize(n*2+1);
    f.push_back(x);
    g.push_back(y);
    int lsb=(n+2)&-(n+2);
    for (int log=0;1<<log<=lsb;log++){
      int d=1<<log;
      if (d*2==n+2){
        fps f1(d*2),g1(d*2);
        int l=d-1;
        for (int i=0;i<d;i++) f1[i]=f[l+i];
        for (int i=0;i<d;i++) g1[i]=g[l+i];
        f1.NTT();g1.NTT();
        vf.push_back(f1);vg.push_back(g1);
        for (int i=0;i<2*d;i++) f1[i]*=g1[i];
        f1.NTT(true);
        for (int i=0;i<d*2;i++) h[l*2+i]+=f1[i];
        break;
      }
      else{
        int l1=n+1-d,l2=d-1;
        fps f1(d*2),g1(d*2);
        for (int i=0;i<d;i++) f1[i]=f[l1+i];
        for (int i=0;i<d;i++) g1[i]=g[l1+i];
        f1.NTT();g1.NTT();
        for (int i=0;i<d*2;i++) f1[i]=f1[i]*vg[log][i]+vf[log][i]*g1[i];
        f1.NTT(true);
        for (int i=0;i<d*2;i++) h[l1+l2+i]+=f1[i];
      }
    }
    return h[n++];
  }
};
