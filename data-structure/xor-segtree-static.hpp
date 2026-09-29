#pragma once

template<typename S,S (*op)(S,S),S (*e)()>
struct XorSegmentTreeStatic{
  int n,log;
  int xorval;
  vector<vector<S>> table;
  XorSegmentTreeStatic(vector<S> v){
    n=v.size();
    log=0;
    while (1<<log<n) log++;
    assert(n==1<<log);
    xorval=0;
    table=vector(log+1,vector<S>(n));
    table[log]=v;
    for (int d=log-1;d>=0;d--) for (int i=0;i<1<<d;i++) update(d,i);
  }
  S get(int p){
    assert(0<=p&&p<n);
    return table[log][p^xorval];
  }
  S prod(int l,int r){
    assert(0<=l&&l<=r&&r<=n);
    return prod(0,n,l,r,0);
  }
  void operate_xor(int x){
    assert(0<=x&&x<n);
    xorval^=x;
  }
private:
  S prod(int l,int r,int ql,int qr,int dep){
    if (qr<=l||r<=ql) return e();
    if (ql<=l&&r<=qr) return table[dep][l^xorval];
    int mid=(l+r)/2;
    return op(prod(l,mid,ql,qr,dep+1),prod(mid,r,ql,qr,dep+1));
  }
  void update(int d,int p){
    int l=p<<(log-d);
    int h=1<<(log-d-1);
    for (int i=0;i<n>>(d+1);i++){
      table[d][l+i]=op(table[d+1][l+i],table[d+1][l+h+i]);
      table[d][l+h+i]=op(table[d+1][l+h+i],table[d+1][l+i]);
    }
  }
};
