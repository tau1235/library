#pragma once

template<typename S,S (*op)(S,S),S (*e)()>
struct SegTree{
  int n;
  int sz;
  vector<S> node;
  SegTree(int n){*this=SegTree<S,op,e>(vector<S>(n,e()));}
  SegTree(vector<S> v){
    sz=v.size();
    n=1; while (n<sz) n*=2;
    node.assign(2*n,e());
    for (int i=0;i<sz;i++) node[i+n]=v[i];
    for (int i=n-1;i>=1;i--) node[i]=op(node[2*i],node[2*i+1]);
  }

  void set(int x,S val){
    x+=n;
    node[x]=val;
    while (x>0){
      x>>=1;
      node[x]=op(node[x*2],node[x*2+1]);
    }
  }
  
  S get(int x){
    x+=n;
    return node[x];
  }

  S prod(int l,int r){
    assert(0<=l&&l<=r&&r<=sz);
    l+=n;r+=n;
    S vl=e(),vr=e();
    while (l<r){
      if (l%2==1) vl=op(vl,node[l++]);
      if (r%2==1) vr=op(node[--r],vr);
      l>>=1;r>>=1;
    }
    return op(vl,vr);
  }

  template<bool (*f)(S)>
  int max_right(int l=0){
    if (l==sz) return sz;
    l+=n;
    S p=e();
    while (true){
      while (l%2==0) l>>=1;
      if (!(f(op(p,node[l])))){
        while (l<n){
          l<<=1;
          if (f(op(p,node[l]))){
            p=op(p,node[l]);
            l++;
          }
        }
        return l-n;
      }
      p=op(p,node[l]);
      l++;
      if ((l&-l)==l) break;
    }
    return sz;
  }
};
