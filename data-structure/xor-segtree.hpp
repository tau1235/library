#pragma once

template<typename S,S (*op)(S,S),S (*e)(),int NODES=(int)1e7>
struct XorSegmentTree{
  using ll=long long;
  struct Node{
    Node* next[2];
    S val;
    Node(){}
  };
  Node *root;
  ll xorval;
  int pid;
  Node *pool;
  int log;
  XorSegmentTree(ll n){
    log=0;
    while (1LL<<log<n) log++;
    assert(n==1LL<<log);
    xorval=0;
    pool=new Node[NODES];
    pid=0;
    root=newNode();
  }
  XorSegmentTree(const vector<S> &v){
    *this=XorSegmentTree((int)v.size());
    auto dfs=[&](auto dfs,ll l,ll r)-> Node* {
      if (r-l==1){
        if (l<(int)v.size()){
          Node* t=newNode();
          t->val=v[l];
          return t;
        }
        else return newNode();
      }
      ll mid=(l+r)/2;
      Node* t=newNode();
      return merge(t,dfs(dfs,l,mid),dfs(dfs,mid,r));
    };
    root=dfs(dfs,0,1<<log);
  }
  void set(ll p,S x){
    assert(0<=p&&p<1LL<<log);
    set(root,0,1LL<<log,p,0,x);
  } 
  S get(ll p){
    assert(0<=p&&p<1LL<<log);
    return get(root,0,1LL<<log,p,0);
  }
  S prod(ll l,ll r){
    assert(0<=l&&l<=r&&r<=1LL<<log);
    return prod(root,0,1LL<<log,l,r,0);
  }
  template<bool (*g)(S)> ll max_right(ll l){
    assert(0<=l&&l<1LL<<log);
    assert(g(e()));
    S p=e();
    return max_right<g>(root,0,1LL<<log,l,0,p);
  }
  void operate_xor(ll x){xorval^=x;}
private:
  Node* newNode(){
    assert(pid<NODES);
    pool[pid].next[0]=nullptr;
    pool[pid].next[1]=nullptr;
    pool[pid].val=e();
    return &pool[pid++];
  }
  Node* merge(Node* t,Node* l,Node* r){
    t->next[0]=l;
    t->next[1]=r;
    t->val=op(l?l->val:e(),r?r->val:e());
    return t;
  }
  Node* set(Node* t,ll l,ll r,ll p,int dep,const S &x){
    if (!t) t=newNode();
    if (r-l==1){
      t->val=x;
      return t;
    }
    int b0=xorval>>(log-dep-1)&1;
    ll mid=(l+r)/2;
    if (p>>(log-dep-1)&1) return merge(t,t->next[b0],set(t->next[b0^1],mid,r,p,dep+1,x));
    else return merge(t,set(t->next[b0],l,mid,p,dep+1,x),t->next[b0^1]);
  }
  S get(Node* t,ll l,ll r,ll p,int dep){
    if (!t) return e();
    if (r-l==1) return t->val;
    int b0=xorval>>(log-dep-1)&1;
    ll mid=(l+r)/2;
    if (p>>(log-dep-1)&1) return get(t->next[b0^1],mid,r,p,dep+1);
    else return get(t->next[b0],l,mid,p,dep+1);
  }
  S prod(Node* t,ll l,ll r,ll ql,ll qr,int dep){
    if (!t) return e();
    if (qr<=l||r<=ql) return e();
    if (ql<=l&&r<=qr) return t->val;
    int b0=xorval>>(log-dep-1)&1;
    ll mid=(l+r)/2;
    return op(prod(t->next[b0],l,mid,ql,qr,dep+1),prod(t->next[b0^1],mid,r,ql,qr,dep+1));
  }
  template<bool (*g)(S)> ll max_right(Node* t,ll l,ll r,ll ql,int dep,S &p){
    if (r<=ql) return r;
    if (ql<=l&&g(op(p,t->val))){
      p=op(p,t->val);
      return r;
    }
    if (r-l==1) return l;
    int b0=xorval>>(log-dep-1)&1;
    ll mid=(l+r)/2;
    if (!t->next[b0]) t->next[b0]=newNode();
    ll k=max_right<g>(t->next[b0],l,mid,ql,dep+1,p);
    if (k!=mid) return k;
    if (!t->next[b0^1]) t->next[b0^1]=newNode();
    return max_right<g>(t->next[b0^1],mid,r,ql,dep+1,p);
  }
};
