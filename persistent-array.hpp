#pragma once

template<typename T,int log=2>
struct PersistentArray{
  struct Node{
    T val;
    array<Node*,log> next;
    Node():val(T()){for (int i=0;i<log;i++) next[i]=nullptr;}
    Node(T x):val(x){for (int i=0;i<log;i++) next[i]=nullptr;}
  };
  vector<Node*> roots;
  PersistentArray(){
    roots.push_back(new Node());
  }
  PersistentArray(vector<T> a){
    Node* root=new Node();
    for (int i=0;i<(int)a.size();i++) set_mut(root,i,a[i]);
    roots.push_back(root);
  }

  Node* clone(Node* t){
    Node* ret=new Node();
    ret->val=t->val;
    ret->next=t->next;
    return ret;
  }
  Node* set_mut(Node* t,int p,T x){
    if (!t) t=new Node();
    if (p==0){
      t->val=x;
      return t;
    }
    t->next[p%log]=set(t->next[p%log],p/log,x);
    return t;
  }
  Node* set(Node* t,int p,T x){
    t=t?clone(t):new Node();
    if (p==0){
      t->val=x;
      return t;
    }
    t->next[p%log]=set(t->next[p%log],p/log,x);
    return t;
  }
  void set(int t,int p,T x){roots.push_back(set(roots[t],p,x));}
  void set(int p,T x){set(prev(),p,x);}
  T get(Node* t,int p){
    if (!t) return T();
    if (p==0) return t->val;
    return get(t->next[p%log],p/log);
  }
  T get(int t,int p){return get(roots[t],p);}
  T get(int p){return get(prev(),p);}
  T operator[](int i){return get(i);}
  int prev(){return (int)roots.size()-1;}
};
