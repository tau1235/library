#pragma once

template<typename T,T (*e)()>
struct DynamicLiChaoTree{
  struct Line{
    T a,b;
    Line():a(0),b(e()){}
    Line(T a,T b):a(a),b(b){}
    T get(T x){return T(a*x+b);};
  };
  struct Node{
    Line line;
    Node *l,*r;
    Node(){(*this)=Node(Line());}
    Node(Line x){
      line=x;
      l=r=nullptr;
    }
  };
  T lx,rx;
  Node* root;

  DynamicLiChaoTree(T lx,T rx):lx(lx),rx(rx){root=new Node(Line());}

  void add(T a,T b){add(root,Line(a,b),lx,rx);}
  void add(Node*& t,Line x,T l,T r){
    if (!t) t=new Node();
    T mid=(l+r)/2;
    bool fl=t->line.get(l)<=x.get(l);
    bool fmid=t->line.get(mid)<=x.get(mid);
    bool fr=t->line.get(r-1)<=x.get(r-1);
    if (fl&&fr) return;
    if (!fl&&!fr){
      swap(t->line,x);
      return;
    }
    if (!fmid){
      swap(t->line,x);
      fl^=1;
      fr^=1;
    }
    if (fr) add(t->l,x,l,mid);
    if (fl) add(t->r,x,mid,r);
  }
  void add_seg(T l,T r,T a,T b){add_seg(root,Line(a,b),lx,rx,l,r);}
  void add_seg(Node*& t,Line x,T a,T b,T l,T r){
    if (b<=l||r<=a) return;
    if (!t) t=new Node();
    if (l<=a&&b<=r){
      add(t,x,a,b);
      return;
    }
    T mid=(a+b)/2;
    add_seg(t->l,x,a,mid,l,r);
    add_seg(t->r,x,mid,b,l,r);
  }
  T query(T x){return query(root,x,lx,rx);}
  T query(Node*& t,T x,T l,T r){
    if (!t) return e();
    if (r-l==1) return t->line.get(x);
    T mid=(l+r)/2;
    if (l<=x&&x<mid) return min(t->line.get(x),query(t->l,x,l,mid));
    if (mid<=x&&x<r) return min(t->line.get(x),query(t->r,x,mid,r));
    assert(0);
  }
};
