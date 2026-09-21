#pragma once

template<typename mint>
struct FormalPowerSeries:vector<mint>{
  using FPS=FormalPowerSeries;
  using ll=long long;
  using vector<mint>::vector;
  static constexpr ll mod=998244353;
  static const int max_log=23;
  inline static vector<mint> proot,iproot;
  inline static vector<int> bitrev;
  static void precalc(){
    if (proot.size()) return;
    const mint pr=3;
    proot.assign(max_log+1,0);
    iproot.assign(max_log+1,0);
    for (int i=0;i<=max_log;i++){
      proot[i]=pr.pow((mod-1)>>i);
      iproot[i]=pr.pow((mod-1)>>i).inv();
    }
    bitrev.assign(1<<max_log,0);
    for (int i=0;i<1<<max_log;i++){
      int rev=0;
      for (int k=0;k<max_log;k++) rev|=((i>>k)&1)<<(max_log-k-1);
      bitrev[i]=rev;
    }
    return;
  }
  void NTT(FPS &a,bool inverse=false){
    precalc();
    int n=a.size();
    int log=0;
    while (n>1<<log) log++;
    for (int i=0;i<n;i++){
      int rev=bitrev[i]>>(max_log-log);
      if (rev>i){
        mint tmp=a[rev];
        a[rev]=a[i];
        a[i]=tmp;
      }
    }
    for (int k=1;k<=log;k++){
      int len=1<<k;
      mint zeta=proot[k];
      if (inverse) zeta=iproot[k];
      mint x=1;
      for (int i=0;i<len/2;i++){
        for (int j=i;j<n;j+=len){
          mint r1=a[j],r2=x*a[j+len/2];
          a[j]=r1+r2;
          a[j+len/2]=r1-r2;
        }
        x*=zeta;
      }
    }
    if (inverse){
      mint ninv=mint(n).inv();
      for (int i=0;i<n;i++) a[i]*=ninv;
    }
    return;
  }
  void NTT(bool inverse=false){NTT(*this,inverse);}
  static FPS convolution(FPS a,FPS b){
    int na=a.size(),nb=b.size();
    int nc=na+nb-1;
    int n=1;
    while (n<nc) n<<=1;
    while ((int)a.size()<n) a.push_back(0);
    while ((int)b.size()<n) b.push_back(0);
    a.NTT();b.NTT();
    for (int i=0;i<n;i++) a[i]*=b[i];
    a.NTT(true);
    a.resize(nc);
    return a;
  }
  void shrink(){while((*this).size()&&(*this).back()==0)(*this).pop_back();}
  FPS rev()const{
    FPS ret(*this);
    reverse(ret.begin(),ret.end());
    return ret;
  }
  FPS pre(int sz)const{
    FPS ret(min((int)(*this).size(),sz));
    for (int i=0;i<min((int)(*this).size(),sz);i++) ret[i]=(*this)[i];
    if ((int)ret.size()<sz) ret.resize(sz);
    return ret;
  }

  FPS operator+=(const FPS &r){
    if ((*this).empty()) (*this).resize(1);
    for (int i=0;i<(int)r.size();i++) (*this)[i]+=r[i];
    return *this;
  }
  FPS operator+=(const mint &r){
    if ((*this).empty()) (*this).resize(1);
    (*this)[0]+=r;
    return *this;
  }
  FPS operator-=(const FPS &r){
    if ((*this).empty()) (*this).resize(1);
    for (int i=0;i<(int)r.size();i++) (*this)[i]-=r[i];
    return *this;
  }
  FPS operator-=(const mint &r){
    if ((*this).empty()) (*this).resize(1);
    (*this)[0]-=r;
    return *this;
  }
  FPS operator*=(const FPS &r){
    if ((*this).empty()||r.empty()){
      (*this).clear();
      return *this;
    }
    return *this=convolution(*this,r);
  }
  FPS operator*=(const mint &r){
    for (int i=0;i<(int)(*this).size();i++) (*this)[i]*=r;
    return *this;
  }
  FPS operator/=(const FPS &r){
    if ((*this).size()<r.size()){
      (*this).clear();
      return *this;
    }
    int n=(*this).size()-r.size()+1;
    return *this=((*this).rev().pre(n)*r.rev().inv(n)).pre(n).rev();
  }
  FPS operator%=(const FPS &r){
    *this-=*this/r*r;
    shrink();
    return *this;
  }

  FPS operator+(const FPS &r)const{return FPS(*this)+=r;}
  FPS operator+(const mint &r)const{return FPS(*this)+=r;}
  FPS operator-(const FPS &r)const{return FPS(*this)-=r;}
  FPS operator-(const mint &r)const{return FPS(*this)-=r;}
  FPS operator*(const FPS &r)const{return FPS(*this)*=r;}
  FPS operator*(const mint &r)const{return FPS(*this)*=r;}
  FPS operator/(const FPS &r)const{return FPS(*this)/=r;}
  FPS operator%(const FPS &r)const{return FPS(*this)%=r;}

  FPS inv(int deg=-1)const{
    assert((*this)[0]!=mint(0));
    if (deg==-1) deg=(*this).size();
    FPS ret(deg);
    ret[0]=(*this)[0].inv();
    for (int d=1;d<deg;d<<=1){
      FPS f(2*d),g(2*d);
      for (int i=0;i<min((int)(*this).size(),2*d);i++) f[i]=(*this)[i];
      for (int i=0;i<d;i++) g[i]=ret[i];
      f.NTT();g.NTT();
      for (int i=0;i<2*d;i++) f[i]*=g[i];
      f.NTT(true);
      for (int i=0;i<d;i++) f[i]=0;
      f.NTT();
      for (int i=0;i<2*d;i++) f[i]*=g[i];
      f.NTT(true);
      for (int i=d;i<min(2*d,deg);i++) ret[i]=-f[i];
    }
    return ret.pre(deg);
  }
  FPS diff()const{
    int n=(*this).size();
    FPS ret(max(0,n-1));
    for (int i=1;i<n;i++) ret[i-1]=(*this)[i]*i;
    return ret;
  }
  FPS integral()const{
    int n=(*this).size();
    FPS ret(n+1);
    ret[0]=0;
    for (int i=1;i<=n;i++) ret[i]=(*this)[i-1]/i;
    return ret;
  }
  FPS log(int deg=-1)const{
    assert((*this)[0]==1);
    if (deg==-1) deg=(*this).size();
    return ((*this).diff()*(*this).inv(deg)).pre(deg-1).integral();
  }
  FPS exp(int deg=-1)const{
    assert((*this)[0]==0);
    int n=(*this).size();
    if (deg==-1) deg=n;
    FPS ret(1);
    ret[0]=1;
    for (int d=1;d<deg;d<<=1) ret=(ret*(pre(d*2)-ret.log(d*2)+1)).pre(d*2);
    return ret.pre(deg);
  }
  FPS pow(ll k,int deg=-1)const{
    int n=(*this).size();
    if (deg==-1) deg=n;
    FPS ret(n);
    ll shift=-1;
    mint a=1,ainv=1;
    for (int i=0;i<n;i++){
      if ((*this)[i].val()){
        shift=i;
        a=(*this)[i];
        ainv=a.inv();
        break;
      }
    }
    if (shift==-1){
      if (k==0) ret[0]=1;
      return ret.pre(deg);
    }
    if (__int128_t(shift)*k>=deg) return FPS(deg);
    for (int i=shift;i<n;i++) ret[i-shift]=(*this)[i]*ainv;
    ret=(ret.log()*k).exp();
    a=a.pow(k);
    shift*=k;
    for (int i=n-1;i>=shift;i--) ret[i]=ret[i-shift]*a;
    for (int i=0;i<shift;i++) ret[i]=0;
    return ret.pre(deg);
  }
};
