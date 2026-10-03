---
title: XOR Segment Tree (noncommutative)
documentation_of: data-structure/xor-segtree-noncommutative.hpp
---

[XOR Segment Tree](https://tau1235.github.io/library/data-structure/xor-segtree.hpp) を非可換なモノイド用にしたもの。[XOR Segment Tree (Static)](https://tau1235.github.io/library/data-structure/xor-segtree-static.hpp) と違い更新も比較的速めにでき、更新と総積取得の計算量のバランスを取っているという感じになっている。使い方などは他とほぼ同じなので省略し、仕組みについて少し書いた。  

これがとても分かりやすい [https://yukicoder.me/problems/no/2265/editorial](https://yukicoder.me/problems/no/2265/editorial)

- 構築 $O(N\log N)$  
- 区間総積取得 $O(\sqrt{N})$  
- 一点更新 $O(\sqrt{N})$

空間計算量のオーダーは [XOR Segment Tree (Static)](https://tau1235.github.io/library/data-structure/xor-segtree-static.hpp) と同じく $O(N\log N)$ ではあるが、その半分くらいの空間計算量になっている。

基本的な仕組みは [XOR Segment Tree (Static)](https://tau1235.github.io/library/data-structure/xor-segtree-static.hpp) と変わらない。  
これをセグメント木の下半分だけについて行う、つまり長さ $2^{(\log N)/2}=\sqrt{N}$ までのノードについて持つべき総積を全て計算しておくことにする。  

これらの情報から区間総積を求めることは高々 $\sqrt{N}+\log N$ 個くらいのノードから総積を得ることによりできる。これは、通常のセグメント木で区間総積を得るための区間の分割の仕方について、長さ $\sqrt{N}$ 以上の区間をいくつかの長さ $\sqrt{N}$ の区間に分割する、というのをすればいい。この分割において長さ $\sqrt{N}$ 以上の区間の個数は $\sqrt{N}$ 個以下であり、それ以外の区間は通常のセグメント木の分割と同じように $\log N$ 個以下であることが分かるので、できた。  
もちろん実際に総積を求めるのも $O(\sqrt{N}+\log N)$ でできて、例えば再帰での実装をするときに高さ $(\log N)/2$ 以下になるまで再帰を打ち切らず続けることをすればいい。この再帰が呼ばれる回数について、`h<=m` によってどれだけ増えるかが気になるが、長さ $n$ のセグメント木のノードの個数が全部で $2n-1$ 個であるのと同じように $2\sqrt{N}-1$ とかで抑えられる。
```cpp
// Static
S prod(int l,int r,int ql,int qr,int h){
  if (qr<=l||r<=ql) return e();
  if (ql<=l&&r<=qr) return table[h][l^xorval];
  int mid=(l+r)/2;
  return op(prod(l,mid,ql,qr,h-1),prod(mid,r,ql,qr,h-1));
}

// h<=m (m=(logn)/2) を追加するだけ
S prod(int l,int r,int ql,int qr,int h){
  if (qr<=l||r<=ql) return e();
  if (ql<=l&&r<=qr&&h<=m) return table[h][l^xorval];
  int mid=(l+r)/2;
  return op(prod(l,mid,ql,qr,h-1),prod(mid,r,ql,qr,h-1));
}
```

一点更新も $\sqrt{N}$ でできる。  
ある更新によって影響を受ける総積の値というのは $O(\sqrt{N})$ 個になるので、それらをそのまま更新すれば $O(\sqrt{N})$ でできる。

余談 1  
高さ $B\ (0\le B\le \log N)$ までのノードについて総積を計算する、という風に考えると

- 構築 $O(NB)$
- 区間総積取得 $O(N/2^B+\log N)$
- 一点更新 $O(2^B)$

とかになるが、当然 $B=\log N$ としたものが Static の方の実装と計算量が一致し、$B=(\log N)/2$ としたものがこれと一致することが確かめられ、これが最適っぽいことも分かる。

余談 2  
区間作用も遅延を上手くやれば $O(\sqrt{N})$ にできる気がしている。ノードに持たせる `lazy` はそのノードが持つ `table` にまだ作用させてない作用を持つことにする。そうすればあるノードの総積を取得するとき `table` とそのノードが持つ `lazy` を作用させるのをクエリごとに毎回することにすればサボれる。1 クエリで必要な値はノードあたり一つの `x` についての `table[h][l^x]` だから、そのノードの総積を取るときに毎回そのノードがもっている `lazy` を作用させて `mapping(lazy,table[h][l^x])` を得るようににしても問題ない。`h<m` のノードを見たいときもあるが、これは上から普通に `push` して全更新しても合計 $O(\sqrt{N})$ になるはず。実装してないから本当にできるかは知らない。

余談 3  
xor だけでなく or,and など任意のビット演算でもできるはず。  
ただ、この `operate_xor` みたいに毎回置き換える感じでやろうとすると区間のコピーっぽいことが必要になりそうで面倒そう ( どれくらい高速になるかもあんま考えてないけど )。  
クエリごとに xor する値を要求するような形式なら、再帰をするとき左右両方が同じ bit に潜る可能性があることに気をつければいいだけなのでそこまで変更をせずに実装できるはず。

## 参考

[https://yukicoder.me/problems/no/2265/editorial](https://yukicoder.me/problems/no/2265/editorial)

[https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp](https://ssrs-cp.github.io/cp_library/data_structure/sequence/xor_segment_tree.hpp)

[https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp](https://maspypy.github.io/library/ds/segtree/xor_segtree.hpp)

[https://codeforces.com/blog/entry/105723](https://codeforces.com/blog/entry/105723)