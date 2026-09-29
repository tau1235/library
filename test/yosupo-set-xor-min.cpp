// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/set_xor_min

#include<bits/stdc++.h>
using namespace std;

#include"other/io.hpp"
#include"data-structure/binary-trie.hpp"

int main(){
  int q;
  cin>>q;
  BinaryTrie<30,int> bt;
  while (q--){
    int t,x;
    cin>>t>>x;
    if (t==0) if (!bt.count(x)) bt.add(x);
    if (t==1) if (bt.count(x)) bt.erase(x);
    if (t==2){
      bt.operate_xor(x);
      cout<<bt.min_element()<<"\n";
      bt.operate_xor(x);
    }
  }
}
