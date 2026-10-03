---
title: XOR Segment Tree (Static)
documentation_of: data-structure/xor-segtree-static.hpp
---

[XOR Segment Tree](https://tau1235.github.io/library/data-structure/xor-segtree.hpp) を非可換なモノイド用にしたもの。ただし、列が Static である、つまり変更はできないという条件つき。  

- 構築 $O(N\log N)$  
- 区間総積取得 $O(\log N)$  
- 更新不可

という感じ。こっちは動的でないので $N$ の大きさに注意する。  
空間計算量が $O(N\log N)$ になるのにも注意。

区間 $\lbrack a\times2^k,(a+1)\times2^k)$ の情報を持つノードについて、可換の場合はただその総積をひとつ持てば良い。  
一方非可換の場合は xor する値によって掛ける順番が変わりうるが、そのすべての場合の総積を持つようにすればいい。この実装では `table[h][l+x]` に $op(v\lbrack l\oplus x\rbrack,v\lbrack (l+1)\oplus x\rbrack,\dots,v\lbrack (l+2^h-1)\oplus x\rbrack)\ (0\le x\lt 2^h)$ を持つようにしている。  
掛ける順番というのは xor する値 $x$ の $\mod{2^k}$ によって決まるから、$2^k$ 通りの総積を持てば良いことが分かる。セグメント木の形を考えるとすべてのノードが持つべき総積の数を合計しても $N\log N$ 個なので上手くいく。  
どの値もそれぞれ $O(1)$ 回の計算で下から求められるので、構築がノードの数と同じで $O(N\log N)$ できることが分かる。  
更新もできなくはないが、一点変更したときに変更すべき値の数が $2N$ 個くらいになってしまうので困る。

更新もしたい場合は [Xor Segment Tree (noncommutative)](https://tau1235.github.io/library/data-structure/xor-segtree-noncommutative.hpp) を使うといい。

## 参考

[https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp](https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp)

[https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp](https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp)

[https://codeforces.com/blog/entry/105723](https://codeforces.com/blog/entry/105723)