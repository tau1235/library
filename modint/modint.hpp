#pragma once

template<int mod> struct modint{
  int x;
  modint():x(0){}
  modint(long long x_){
    x_%=mod;
    if (x_<0) x_+=mod;
    x=(int)x_;
  }
  static modint raw(int x_){
    modint ret;
    ret.x=x_;
    return ret;
  }
  int val()const{return x;}
  modint& operator+=(const modint &r){
    x+=r.x;
    if (x>=mod) x-=mod;
    return *this;
  }
  modint& operator-=(const modint &r){
    x-=r.x;
    if (x<0) x+=mod;
    return *this;
  }
  modint& operator*=(const modint &r){
    x=(int)((long long)x*r.x%mod);
    return *this;
  }
  modint& operator/=(const modint &r){return *this*=r.inv();}
  friend modint operator+(const modint &l,const modint &r){return modint(l)+=r;}
  friend modint operator-(const modint &l,const modint &r){return modint(l)-=r;}
  friend modint operator*(const modint &l,const modint &r){return modint(l)*=r;}
  friend modint operator/(const modint &l,const modint &r){return modint(l)/=r;}
  modint operator+()const{return *this;}
  modint operator-()const{return modint()-*this;}
  modint& operator++(){
    if (++x==mod) x=0;
    return *this;
  }
  modint& operator--(){
    if (x--==0) x=mod-1;
    return *this;
  }
  modint operator++(int){
    modint ret=*this;
    if (++x==mod) x=0;
    return ret;
  }
  modint operator--(int){
    modint ret=*this;
    if (x--==0) x=mod-1;
    return ret;
  } 
  friend bool operator==(const modint &l,const modint &r){return l.x==r.x;}
  friend bool operator!=(const modint &l,const modint &r){return l.x!=r.x;}
  modint inv()const{
    int a=mod,b=x,u=0,v=1;
    while (b){
      int q=a/b;
      swap(a-=q*b,b);
      swap(u-=q*v,v);
    }
    if (u<0) u+=mod;
    return modint::raw(u);
  }
  modint pow(unsigned long long k)const{
    modint ret=1,pw=*this;
    while (k){
      if (k&1) ret*=pw;
      pw*=pw;
      k>>=1;
    }
    return ret;
  }
  friend istream &operator>>(istream &is,modint &p){
    long long x;
    is>>x;
    p=modint(x);
    return is;
  }
  friend ostream &operator<<(ostream &os,const modint &p){return os<<p.x;}
};
using modint998244353=modint<998244353>;
using modint1000000007=modint<1000000007>;
