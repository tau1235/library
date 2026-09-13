#pragma once

template<typename S,S (*op)(S,S),S (*e)(),typename F,S (*mapping)(F,S),F (*composition)(F,F),F (*id)()>
struct SplayTree{
  struct Node{
    S key,val,valrev;
    F lazy;
    int cnt;
    bool rev;
    bool has_lazy;
    Node *l,*r,*p;
    Node():key(e()),val(e()),valrev(e()),lazy(id()),cnt(1),rev(false),has_lazy(false),l(nullptr),r(nullptr),p(nullptr){}
  };
  Node* root;
  SplayTree():root(nullptr){}
  SplayTree(vector<S> &a){
    *this=SplayTree();
    int n=a.size();
    auto dfs=[&](auto dfs,Node* p,int l,int r)-> Node* {
      if (r-l<=0) return nullptr;
      int mid=(l+r)/2;
      Node* t=newNode(a[mid]);
      t->p=p;
      t->l=dfs(dfs,t,l,mid);
      t->r=dfs(dfs,t,mid+1,r);
      return update(t);
    };
    root=dfs(dfs,nullptr,0,n);
  }

private:
  inline static const int NODES=1e6;
  inline static Node pool[NODES];
  inline static int pid=0;
  Node* newNode(){
    assert(pid<NODES);
    pool[pid]=Node();
    return &pool[pid++];
  }
  Node* newNode(S val){
    Node* ret=newNode();
    ret->key=ret->val=ret->valrev=val;
    return ret;
  }
  int cnt(Node* t){return t?t->cnt:0;}
  S key(Node* t){return t?t->key:e();}
  S val(Node* t){return t?t->val:e();}
  S valrev(Node* t){return t?t->valrev:e();}
  Node* all_apply(Node* t,F f){
    if (!t) return t;
    t->key=mapping(f,t->key);
    t->val=mapping(f,t->val);
    t->valrev=mapping(f,t->valrev);
    t->lazy=composition(f,t->lazy);
    t->has_lazy=true;
    return t;
  }
  Node* all_reverse(Node* t){
    if (!t) return t;
    t->rev^=true;
    swap(t->val,t->valrev);
    swap(t->l,t->r);
    return t;
  }
  Node* update(Node* t){
    if (!t) return t;
    if (t->l){
      if (t->r){
        t->val=op(op(t->l->val,t->key),t->r->val);
        t->valrev=op(op(t->r->valrev,t->key),t->l->valrev);
        t->cnt=1+t->l->cnt+t->r->cnt;
      }
      else{
        t->val=op(t->l->val,t->key);
        t->valrev=op(t->key,t->l->valrev);
        t->cnt=1+t->l->cnt;
      }
    }
    else{
      if (t->r){
        t->val=op(t->key,t->r->val);
        t->valrev=op(t->r->valrev,t->key);
        t->cnt=1+t->r->cnt;
      }
      else{
        t->val=t->key;
        t->valrev=t->key;
        t->cnt=1;
      }
    }
    return t;
  }
  Node* push(Node* t){
    if (!t) return t;
    if (t->rev){
      all_reverse(t->l);
      all_reverse(t->r);
      t->rev=false;
    }
    if (t->has_lazy){
      all_apply(t->l,t->lazy);
      all_apply(t->r,t->lazy);
      t->lazy=id();
      t->has_lazy=false;
    }
    return t;
  }
  Node*& ppc(Node* p){
    if (p->p->l==p) return p->p->l;
    else return p->p->r;
  }
  void rotR(Node* t){
    assert(t->p);
    Node* p=t->p;
    t->p=p->p;
    if (p->p) ppc(p)=t;
    p->p=t;
    if (t->r) t->r->p=p;
    p->l=t->r;
    t->r=p;
  }
  void rotL(Node* t){
    assert(t->p);
    Node* p=t->p;
    t->p=p->p;
    if (p->p) ppc(p)=t;
    p->p=t;
    if (t->l) t->l->p=p;
    p->r=t->l;
    t->l=p;
  }
  void rotate(Node* t){
    assert(t->p);
    if (t->p->l==t) rotR(t);
    else rotL(t);
  }
  Node* splay(Node* t){
    push(t);
    while (t->p){
      Node* p=t->p;
      if (!p->p){
        rotate(t);
        update(p);
        update(t);
      }
      else{
        Node* pp=p->p;
        push(pp);
        push(p);
        push(t);
        if (p->l==t){
          if (pp->l==p) rotate(p),rotate(t);
          else rotate(t),rotate(t);
        }
        else{
          if (pp->r==p) rotate(p),rotate(t);
          else rotate(t),rotate(t);
        }
        update(pp);
        update(p);
        update(t);
      }
    }
    return update(t);
  }
  Node* find(Node* &t,int k){
    assert(0<=k&&k<cnt(t));
    while (true){
      push(t);
      if (cnt(t->l)==k) break;
      if (cnt(t->l)<k){
        k-=cnt(t->l)+1;
        t=t->r;
      }
      else t=t->l;
    }
    return splay(t);
  }
  Node* insert(Node* &t,int k,S val){
    assert(0<=k&&k<=cnt(t));
    Node* x=newNode(val);
    if (k==cnt(t)){
      x->l=t;
      if (t) t->p=x;
      return t=update(x);
    }
    Node* p=find(t,k);
    x->l=p->l;
    x->r=p;
    if (p->l) p->l->p=x;
    p->l=nullptr;
    p->p=x;
    update(p);
    return t=update(x);
  }
  Node* erase(Node* &t,int k){
    assert(0<=k&&k<cnt(t));
    Node* p=find(t,k);
    if (k==0){
      if (p->r) p->r->p=nullptr;
      return t=p->r;
    }
    if (k==cnt(p)-1){
      if (p->l) p->l->p=nullptr;
      return t=p->l;
    }
    p->r->p=nullptr;
    Node* r=find(p->r,0);
    r->l=p->l;
    p->l->p=r;
    return t=update(r);
  }
  Node* between(Node* &t,int l,int r){
    assert(0<=l&&l<=r&&r<=cnt(t));
    if (l==r) return nullptr;
    if (l==0&&r==cnt(t)) return t;
    if (l==0) return (t=splay(find(t,r)))->l;
    if (r==cnt(t)) return (t=splay(find(t,l-1)))->r;
    Node* pr=splay(find(t,r));
    pr->l->p=nullptr;
    Node* pl=splay(find(pr->l,l-1));
    pl->p=pr;
    pr->l=pl;
    t=update(pr);
    return pl->r;
  }
  Node* merge(Node* l,Node* r){
  }
  pair<Node*,Node*> split(Node* t,int k){
  }
  tuple<Node*,Node*,Node*> split(Node* t,int l,int r){
  }
  S get(Node* &t,int k){
    assert(0<=k&&k<cnt(t));
    find(t,k);
    return key(t);
  }
  S prod(Node* &t,int l,int r){
    assert(0<=l&&l<=r&&r<=cnt(t));
    return val(between(t,l,r));
  }
  Node* apply(Node* &t,int l,int r,F f){
    assert(0<=l&&l<=r&&r<=cnt(t));
    Node* p=between(t,l,r);
    if (!p) return t;
    all_apply(p,f);
    return t=splay(p);
  }
  Node* reverse(Node* &t,int l,int r){
    assert(0<=l&&l<=r&&r<=cnt(t));
    Node* p=between(t,l,r);
    if (!p) return t;
    all_reverse(p);
    return t=splay(p);
  }
public:
  void insert(int p,S x){insert(root,p,x);}
  void erase(int p){erase(root,p);}
  S get(int p){return get(root,p);}
  S prod(int l,int r){return prod(root,l,r);}
  void apply(int l,int r,F f){apply(root,l,r,f);}
  void reverse(int l,int r){reverse(root,l,r);}
  int size(){return cnt(root);}
};
