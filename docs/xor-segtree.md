---
title: XOR Segment Tree
documentation_of: data-structure/xor-segtree.hpp
---

Segment Tree に添え字を $\rm{xor}$ する機能を追加したもの。Binary Trie にモノイドを乗せたものと考えてもいい。  
計算量は時間、空間ともに通常のセグメント木と変わらずにできる。  
また、`operator_xor` は $O(1)$ でできる。

具体的には、以下のようなクエリに高速に答えられる。  
$\sum_{L\le i\le R} A_{i\ \rm{xor}\  x}$  

同様に $\min,\max$ などもできるが、演算が可換であることを必要とする。非可換なモノイドを乗せたい場合、更新をしなくてもよいなら $O(\log N)$ で区間の総積が取れる。

## コンストラクタ
```cpp
(1) XorSegmentTree<S,op,e>(ll n)
(2) XorSegmentTree<S,op,e>(vector<S> v)
```

### 制約
- (1) $n$ は非負整数 $k$ を用いて $2^k$ と表せる
- モノイド `S` の演算 `op` は可換である、つまり $op(a,b)=op(b,a)$ であることが必要。

## operate_xor
```cpp
void operate_xor(ll x)
```

管理している列 $A$ を $B_i=A_{i\ \rm{xor}\  x}$ として定義される列 $B$ で置き換える。

### 計算量
- $O(1)$


## 参考

[https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp](https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp)

[https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp](https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp)

[https://codeforces.com/blog/entry/105723](https://codeforces.com/blog/entry/105723)