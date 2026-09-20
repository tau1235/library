#pragma once

template<typename T,T (*e)()>
struct LiChaoTree{
  struct Line{
    T a,b;
    Line(T a,T b):a(a),b(b){}
    T get(T x){return T(a*x+b);};
  };
  int n,log,n2;
  vector<Line> val;
  vector<T> xs;

  LiChaoTree(vector<T> xs_):xs(xs_){
    xs.push_back(0);
    sort(xs.begin(),xs.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    n2=xs.size();
    log=0;
    while (1<<log<n2) log++;
    n=1<<log;
    while ((int)xs.size()<n) xs.push_back(xs.back()+1);
    val=vector<Line>(n*2,Line(0,e()));
  }

  void add(T a,T b){add(a,b,1,0,n);}
  void add(T a,T b,int idx,int l,int r){
    Line line(a,b);
    int mid=(l+r)/2;
    bool fl=val[idx].get(xs[l])<=line.get(xs[l]),fmid=val[idx].get(xs[mid])<=line.get(xs[mid]),fr=val[idx].get(xs[r-1])<=line.get(xs[r-1]);
    if (fl&&fr) return;
    if (!fl&&!fr){
      swap(val[idx],line);
      return;
    }
    if (!fmid){
      swap(val[idx],line);
      fl^=1;
      fr^=1;
    }
    assert(fl!=fr);
    if (fr) add(line.a,line.b,idx*2,l,mid);
    if (fl) add(line.a,line.b,idx*2+1,mid,r);
  }
  T query(T x){
    int p=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
    assert(xs[p]==x);
    p+=n;
    T ret=e();
    for (int i=0;i<=log;i++) ret=min(ret,val[p>>i].get(x));
    return ret;
  }
};
