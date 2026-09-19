template<typename S,S (*op)(S,S),S (*e)(),typename F,S (*mapping)(F,S),F (*composition)(F,F),F (*id)(),int NODES=(int)1e7>
struct PersistentLazySegmentTree{
  using ll=long long;
  ll n,n2;
  struct Node{
    S val;
    F lazy;
    bool has_lazy;
    Node *l,*r;
    Node(){}
  };
  vector<Node*> roots;
  Node *pool;
  int pid;
  PersistentLazySegmentTree(ll n_){
    n2=n_;
    int log=0;
    while (1LL<<log<n2) log++;
    n=1LL<<log;
    pool=new Node[NODES];
    pid=0;
    Node* root=newNode();
    roots.push_back(root);
  }
  PersistentLazySegmentTree(vector<S> v){
    *this=PersistentLazySegmentTree((int)v.size());
    auto dfs=[&](auto dfs,ll l,ll r)-> Node* {
      if (r-l==1){
        if (l<(int)v.size()) return newNode(v[l],id(),false);
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
    return prod(roots[t],0,n,l,r,id());
  }
  S prod(ll l,ll r){return prod((int)roots.size()-1,l,r);}
  void apply(int t,ll l,ll r,F f){
    assert(0<=l&&l<=r&&r<=n2);
    assert(0<=t&&t<(int)roots.size());
    Node* root=apply(clone(roots[t]),0,n,l,r,f);
    roots.push_back(root);
  }
  void apply(ll l,ll r,F f){apply((int)roots.size()-1,l,r,f);}
  template<bool (*g)(S)> ll max_right(int t,ll l){
    assert(0<=t&&t<(int)roots.size());
    assert(0<=l&&l<n2);
    assert(g(e()));
    S p=e();
    F lazy=id();
    return min(max_right<g>(roots[t],0,n,l,p,lazy),n2);
  }
  template<bool (*g)(S)> ll max_right(ll l){return max_right<g>((int)roots.size()-1,l);}
  template<bool (*g)(S,S)> ll max_right_pair(int t1,int t2,ll l){
    assert(0<=t1&&t1<(int)roots.size());
    assert(0<=t2&&t2<(int)roots.size());
    assert(0<=l&&l<n2);
    assert(g(e(),e()));
    S p1=e(),p2=e();
    F lazy1=id(),lazy2=id();
    return min(max_right_pair<g>(roots[t1],roots[t2],0,n,l,p1,p2,lazy1,lazy2),n2);
  }
  void copy_range(int to,int from,ll l,ll r){
    assert(0<=l&&l<=r&&r<=n2);
    assert(0<=to&&to<(int)roots.size());
    assert(0<=from&&from<(int)roots.size());
    Node* root=copy_range(clone(roots[to]),roots[from],0,n,l,r,id());
    roots.push_back(root);
  }
  int prev(){return (int)roots.size()-1;}
  void reset(){pid=0;}
private:
  Node* newNode(){
    assert(pid<NODES);
    pool[pid].val=e();
    pool[pid].lazy=id();
    pool[pid].has_lazy=false;
    pool[pid].l=pool[pid].r=nullptr;
    return &pool[pid++];
  }
  Node* newNode(S x,F f,bool flag,Node* l=nullptr,Node* r=nullptr){
    Node* ret=newNode();
    ret->val=x;
    ret->lazy=f;
    ret->has_lazy=flag;
    ret->l=l;ret->r=r;
    return ret;
  }
  Node* clone(Node* t){
    Node* ret=newNode();
    ret->val=t->val;
    ret->lazy=t->lazy;
    ret->has_lazy=t->has_lazy;
    ret->l=t->l;ret->r=t->r;
    return ret;
  }
  Node* merge(Node* l,Node* r){return newNode(op(l?l->val:e(),r?r->val:e()),id(),false,l,r);}
  Node* all_apply(Node* t,F f){
    t=t?clone(t):newNode();
    t->val=mapping(f,t->val);
    t->lazy=composition(f,t->lazy);
    t->has_lazy=true;
    return t;
  }
  void push(Node* t){
    if (!t->has_lazy) return;
    t->l=all_apply(t->l,t->lazy);
    t->r=all_apply(t->r,t->lazy);
    t->lazy=id();
    t->has_lazy=false;
  }
  Node* set(Node* t,ll p,S x,ll l,ll r){
    if (!t) t=newNode();
    if (!(l<=p&&p<r)) return t;
    if (r-l==1) return newNode(x,id(),false);
    ll mid=(l+r)/2;
    t=clone(t);
    push(t);
    return merge(set(t->l,p,x,l,mid),set(t->r,p,x,mid,r));
  }
  S prod(Node* t,ll l,ll r,ll a,ll b,F lazy){
    if (!t) return e();
    if (b<=l||r<=a) return e();
    if (a<=l&&r<=b) return mapping(lazy,t->val);
    ll mid=(l+r)/2;
    lazy=composition(lazy,t->lazy);
    return op(prod(t->l,l,mid,a,b,lazy),prod(t->r,mid,r,a,b,lazy));
  }
  Node* apply(Node* t,ll l,ll r,ll a,ll b,F f){
    if (!t) t=newNode();
    if (b<=l||r<=a) return t;
    if (a<=l&&r<=b) return all_apply(t,f);
    ll mid=(l+r)/2;
    push(t);
    return merge(apply(t->l,l,mid,a,b,f),apply(t->r,mid,r,a,b,f));
  }
  template<bool (*g)(S)> ll max_right(Node* t,ll l,ll r,ll ql,S &p,F lazy){
    if (r<=ql) return r;
    if (ql<=l&&g(mapping(lazy,op(p,t->val)))){
      p=mapping(lazy,op(p,t->val));
      return r;
    }
    if (r-l==1) return l;
    ll mid=(l+r)/2;
    lazy=composition(lazy,t->lazy);
    if (!t->l) t->l=newNode();
    ll k=max_right<g>(t->l,l,mid,ql,p,lazy);
    if (k!=mid) return k;
    if (!t->r) t->r=newNode();
    return max_right<g>(t->r,mid,r,ql,p,lazy);
  }
  template<bool (*g)(S,S)> ll max_right_pair(Node* t1,Node* t2,ll l,ll r,ll ql,S &p1,S &p2,F lazy1,F lazy2){
    if (r<=ql) return r;
    if (ql<=l&&g(mapping(lazy1,op(p1,t1->val)),mapping(lazy2,op(p2,t2->val)))){
      p1=mapping(lazy1,op(p1,t1->val));
      p2=mapping(lazy2,op(p2,t2->val));
      return r;
    }
    if (r-l==1) return l;
    ll mid=(l+r)/2;
    lazy1=composition(lazy1,t1->lazy);
    lazy2=composition(lazy2,t2->lazy);
    if (!t1->l) t1->l=newNode();
    if (!t2->l) t2->l=newNode();
    ll k=max_right_pair<g>(t1->l,t2->l,l,mid,ql,p1,p2,lazy1,lazy2);
    if (k!=mid) return k;
    if (!t1->r) t1->r=newNode();
    if (!t2->r) t2->r=newNode();
    return max_right_pair<g>(t1->r,t2->r,mid,r,ql,p1,p2,lazy1,lazy2);
  }
  Node* copy_range(Node* to,Node* from,ll l,ll r,ll a,ll b,F lazy){
    if (b<=l||r<=a) return to;
    if (a<=l&&r<=b) return all_apply(from,lazy);
    ll mid=(l+r)/2;
    if (to) push(to);
    if (from) lazy=composition(lazy,from->lazy);
    return merge(copy_range(to?to->l:nullptr,(from&&from->l)?from->l:nullptr,l,mid,a,b,lazy),
                 copy_range(to?to->r:nullptr,(from&&from->r)?from->r:nullptr,mid,r,a,b,lazy));
  }
};