#pragma once

template<typename S,S (*op)(S,S),S (*e)(),int NODES=(int)2e7>
struct PersistentSegmentTree{
  using ll=long long;
  ll n,n2;
  struct Node{
    S val;
    Node *l,*r;
    Node(){}
  };
  vector<Node*> roots;
  Node *pool;
  int pid;
  PersistentSegmentTree(ll n_){
    n2=n_;
    int log=0;
    while (1LL<<log<n2) log++;
    n=1LL<<log;
    pool=new Node[NODES];
    pid=0;
    Node* root=newNode();
    roots.push_back(root);
  }
  PersistentSegmentTree(vector<S> v){
    *this=PersistentSegmentTree((int)v.size());
    auto dfs=[&](auto dfs,ll l,ll r)-> Node* {
      if (r-l==1){
        if (l<(int)v.size()) return newNode(v[l]);
        else return newNode();
      }
      ll mid=(l+r)/2;
      return merge(dfs(dfs,l,mid),dfs(dfs,mid,r));
    };
    roots[0]=dfs(dfs,0,n);
  }

  void set(int t,ll p,S x){
    assert(0<=p&&p<n2);
    assert(0<=t&&t<(int)roots.size());
    Node* root=set(roots[t],p,x,0,n);
    roots.push_back(root);
  }
  void set(ll p,S x){set((int)roots.size()-1,p,x);}
  S get(int t,ll p){
    assert(0<=t&&t<(int)roots.size());
    assert(0<=p&&p<n2);
    return prod(t,p,p+1);
  }
  S get(ll p){return get((int)roots.size()-1,p);}
  S prod(int t,ll l,ll r){
    assert(0<=l&&l<=r&&r<=n2);
    assert(0<=t&&t<(int)roots.size());
    return prod(roots[t],0,n,l,r);
  }
  S prod(ll l,ll r){return prod((int)roots.size()-1,l,r);}
  template<bool (*g)(S)> ll max_right(int t,ll l){
    assert(0<=t&&t<(int)roots.size());
    assert(0<=l&&l<n2);
    assert(g(e()));
    S p=e();
    return min(max_right<g>(roots[t],0,n,l,p),n2);
  }
  template<bool (*g)(S)> ll max_right(ll l){return max_right<g>((int)roots.size()-1,l);}
  template<bool (*g)(S,S)> ll max_right_pair(int t1,int t2,ll l){
    assert(0<=t1&&t1<(int)roots.size());
    assert(0<=t2&&t2<(int)roots.size());
    assert(0<=l&&l<n2);
    assert(g(e(),e()));
    S p1=e(),p2=e();
    return min(max_right_pair<g>(roots[t1],roots[t2],0,n,l,p1,p2),n2);
  }
  void copy_range(int to,int from,ll l,ll r){
    assert(0<=l&&l<=r&&r<=n2);
    assert(0<=to&&to<(int)roots.size());
    assert(0<=from&&from<(int)roots.size());
    Node* root=copy_range(clone(roots[to]),roots[from],0,n,l,r);
    roots.push_back(root);
  }
  int prev(){return (int)roots.size()-1;}
  void reset(){pid=0;}
private:
  Node* newNode(){
    assert(pid<NODES);
    pool[pid].val=e();
    pool[pid].l=pool[pid].r=nullptr;
    return &pool[pid++];
  }
  Node* newNode(S x,Node* l=nullptr,Node* r=nullptr){
    Node* ret=newNode();
    ret->val=x;
    ret->l=l;ret->r=r;
    return ret;
  }
  Node* clone(Node* t){
    Node* ret=newNode();
    ret->val=t->val;
    ret->l=t->l;ret->r=t->r;
    return ret;
  }
  Node* merge(Node* l,Node* r){return newNode(op(l?l->val:e(),r?r->val:e()),l,r);}
  Node* set(Node* t,ll p,S x,ll l,ll r){
    if (!t) t=newNode();
    if (!(l<=p&&p<r)) return t;
    if (r-l==1) return newNode(x);
    ll mid=(l+r)/2;
    t=t?clone(t):newNode();
    return merge(set(t->l,p,x,l,mid),set(t->r,p,x,mid,r));
  }
  S prod(Node* t,ll l,ll r,ll a,ll b){
    if (!t) return e();
    if (b<=l||r<=a) return e();
    if (a<=l&&r<=b) return t->val;
    ll mid=(l+r)/2;
    return op(prod(t->l,l,mid,a,b),prod(t->r,mid,r,a,b));
  }
  template<bool (*g)(S)> ll max_right(Node* t,ll l,ll r,ll ql,S &p){
    if (r<=ql) return r;
    if (ql<=l&&g(op(p,t->val))){
      p=op(p,t->val);
      return r;
    }
    if (r-l==1) return l;
    ll mid=(l+r)/2;
    if (!t->l) t->l=newNode();
    ll k=max_right<g>(t->l,l,mid,ql,p);
    if (k!=mid) return k;
    if (!t->r) t->r=newNode();
    return max_right<g>(t->r,mid,r,ql,p);
  }
  template<bool (*g)(S,S)> ll max_right_pair(Node* t1,Node* t2,ll l,ll r,ll ql,S &p1,S &p2){
    if (r<=ql) return r;
    if (ql<=l&&g(op(p1,t1->val),op(p2,t2->val))){
      p1=op(p1,t1->val);
      p2=op(p2,t2->val);
      return r;
    }
    if (r-l==1) return l;
    ll mid=(l+r)/2;
    if (!t1->l) t1->l=newNode();
    if (!t2->l) t2->l=newNode();
    ll k=max_right_pair<g>(t1->l,t2->l,l,mid,ql,p1,p2);
    if (k!=mid) return k;
    if (!t1->r) t1->r=newNode();
    if (!t2->r) t2->r=newNode();
    return max_right_pair<g>(t1->r,t2->r,mid,r,ql,p1,p2);
  }
  Node* copy_range(Node* to,Node* from,ll l,ll r,ll a,ll b){
    if (b<=l||r<=a) return to;
    if (a<=l&&r<=b) return from;
    ll mid=(l+r)/2;
    return merge(copy_range(to?to->l:nullptr,(from&&from->l)?from->l:nullptr,l,mid,a,b),
                 copy_range(to?to->r:nullptr,(from&&from->r)?from->r:nullptr,mid,r,a,b));
  }
};
