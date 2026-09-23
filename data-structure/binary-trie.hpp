#pragma once

template<int LOG,typename T,typename S=int,int NODES=(int)1e7>
struct BinaryTrie{
	struct Node{
		Node* next[2];
		S cnt;
		Node(){}
	};
	Node *root;
  T lazy;
  Node *pool;
  int pid;
	BinaryTrie(){
    pool=new Node[NODES];
    pid=0;
		root=newNode();
    lazy=0;
	}
	void add(const T &x,S cnt=1){root=add(root,x,cnt,0);}
	void erase(const T &x,S cnt=1){root=add(root,x,-cnt,0);}
  T get_kth(S k){
    assert(0<=k&&k<root->cnt);
    return get_kth(root,k,0);
  }
  T max_element(){
    assert(root->cnt>0);
    return get_kth(root,root->cnt-1,0);
  }
  T min_element(){
    assert(root->cnt>0);
    return get_kth(root,0,0);
  }
  S count(const T &x){return count(root,x,0);}
  S count_less(const T &x){return count_less(root,x,0);}
  void operate_xor(const T &x){lazy^=x;}
private:
  Node* newNode(){
    assert(pid<NODES);
    pool[pid].next[0]=nullptr;
    pool[pid].next[1]=nullptr;
    pool[pid].cnt=0;
    return &pool[pid++];
  }
  Node* add(Node* t,const T &x,S cnt,int dep){
    if (!t) t=newNode();
    t->cnt+=cnt;
    if (dep==LOG){
      assert(t->cnt>=0);
      return t;
    }
    int bit=(x^lazy)>>(LOG-dep-1)&1;
    t->next[bit]=add(t->next[bit],x,cnt,dep+1);
    return t;
  }
  T get_kth(Node* t,S k,int dep){
    if (dep==LOG) return 0;
    int b0=lazy>>(LOG-dep-1)&1;
    if ((t->next[b0]?t->next[b0]->cnt:0)<=k){
      S ret=get_kth(t->next[b0^1],k-S(t->next[b0]?t->next[b0]->cnt:0),dep+1);
      ret|=T(1)<<(LOG-dep-1);
      return ret;
    }
    else return get_kth(t->next[b0],k,dep+1);
  }
  S count(Node* t,const T &x,int dep){
    if (dep==LOG) return t->cnt;
    int bit=(x^lazy)>>(LOG-dep-1)&1;
    if (bit==0) return t->next[0]?count(t->next[0],x,dep+1):0;
    else return t->next[1]?count(t->next[1],x,dep+1):0;
  }
  S count_less(Node* t,const T &x,int dep){
    if (dep==LOG) return 0;
    int b0=lazy>>(LOG-dep-1)&1;
    S ret=0;
    if ((x>>(LOG-dep-1)&1)&&t->next[b0]) ret+=t->next[b0]->cnt;
    if (t->next[b0^(x>>(LOG-dep-1)&1)]) ret+=count_less(t->next[b0^(x>>(LOG-dep-1)&1)],x,dep+1);
    return ret;
  }
};
