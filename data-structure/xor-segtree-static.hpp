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
    table[0]=v;
    for (int h=1;h<=log;h++) for (int i=0;i<n>>h;i++) update(h,i);
  }
  S get(int p){
    assert(0<=p&&p<n);
    return table[0][p^xorval];
  }
  S prod(int l,int r){
    assert(0<=l&&l<=r&&r<=n);
    return prod(0,n,l,r,log);
  }
  void operate_xor(int x){
    assert(0<=x&&x<n);
    xorval^=x;
  }
private:
  void update(int h,int p){
    assert(1<=h&&h<=log);
    assert(0<=p&&p<n);
    int l=p<<h;
    int hl=1<<(h-1);
    for (int i=0;i<1<<(h-1);i++){
      table[h][l+i]=op(table[h-1][l+i],table[h-1][l+(hl+i)]);
      table[h][l+(hl+i)]=op(table[h-1][l+(hl+i)],table[h-1][l+i]);
    }
  }
  S prod(int l,int r,int ql,int qr,int h){
    if (qr<=l||r<=ql) return e();
    if (ql<=l&&r<=qr) return table[h][l^xorval];
    int mid=(l+r)/2;
    return op(prod(l,mid,ql,qr,h-1),prod(mid,r,ql,qr,h-1));
  }
};
