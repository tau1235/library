---
title: HLD
documentation_of: tree/heavy-light-decomposition.hpp
---

Heavy Light Decomposition、HLD、HL分解、重軽分解など言い方が多い。

木の辺を heavy edge と light edge に分ける。  
頂点 $v$ の子のうち部分木の頂点数が最大である頂点をどれか一つ選び、$v$ とその頂点の間の辺を heavy edge としている。一応他の定義をする場合もあるらしいが、ほとんど見ることはない。  

シンプルだけど色々応用ができて面白い。  
特に、ある頂点から根まで登っていく過程について、light edge を通るたびに部分木の頂点数が 2 倍以上に増えることがさっきの定義から分かるので、根まで登るまでに通る light edge の本数が $O(\log N)$ である、というような性質をよく使う。

euler tour をして頂点を列として並べ、その区間 $O(\log N)$ 個としてパスを分解することができるので、パスクエリを区間クエリに変換できたりするので便利。  

## コンストラクタ
```cpp
HeavyLightDecomposition(int n,int root=0)
```

木の頂点数 $N$、根 $r$ を渡す。根を渡さない場合 $r=0$ となる。

### 計算量
- $O(1)$


## add_edge
```cpp
void add_edge(int u,int v)
```

辺 $(u,v)$ を追加する。

### 制約
- $0\le u,v\lt N$ 

### 計算量
- $O(1)$


## build
```cpp
void build()
```

HLD をする。  
`euler[i]` に $i$ 番目の頂点が、`in[v]` に頂点 $v$ の euler tour におけるインデックスが入る。

### 制約
- これを呼んだときに `add_edge` は合計 $N-1$ 回呼ばれていて、すべての辺が追加されている

### 計算量
- $O(N)$


## path_query
```cpp
void path_query(int u,int v,const F &f,bool vertex=true)
```

パスクエリを処理する。  
頂点 $u$ から $v$ へ向かうパスについて、euler tour における区間に分解したものを `f` に渡す。  
分解した区間それぞれについて、euler tour における区間 $\lbrack l,r)\  (l\le r)$ で `f(int l,int r)` が呼ばれる。このとき $l,r$ は euler tour におけるインデックスであることに注意。  
euler tour におけるインデックスでは $l,l+1,\dots,r-1$ を、頂点番号で言えば $euler[l],euler[l+1],\dots,euler[r-1]$ となる。

$O(\log N)$ 個の区間に分割するので、`f` は $O(\log N)$ 回呼ばれる。

`bool vertex` が `true` のとき頂点に対するクエリを、`false` のとき辺に対するクエリを扱う。  
辺に対するクエリの場合、頂点 $v$ が $v$ とその親をつなぐ辺を表す。

### 制約
- $0\le u,v\lt N$ 


## path_noncommutative_query
```cpp
void path_noncommutative_query(int u,int v,const F &f,bool vertex=true)
```

`path_query` では `f(int l,int r)` が呼ばれるとき必ず $l\le r$ だが、こちらは頂点を訪れる順番も考慮される。アフィン変換などの非可換なクエリを扱うときなどに `path_noncommutative_query` を使うといい。逆に、可換なクエリなら `path_query` のほうが扱いやすいはず。  
$l\le r$ のとき $l,l+1,\dots,r-1$ を、$l\gt r$ なら $l-1,l-2,\dots,r$ を表す。ので、それぞれ区間 $\lbrack l,r),\lbrack r,l)$ を表すという風にも書ける。  

想定される使い方として、セグ木と合わせるような使い方があるが、その場合以下のように書ける。([Vertex Set Path Decomposition](https://judge.yosupo.jp/problem/vertex_set_path_composite) の場合)

```cpp
S op1(S a,S b){return {b.a*a.a,b.a*a.b+b.b};}
S op2(S a,S b){return op1(b,a);}
```
```cpp
g.path_noncommutative_query(u,v,[&](int l,int r){
  if (l<=r) p=op1(p,seg1.prod(l,r));
  else p=op1(p,seg2.prod(r,l));
});
```

それ以外は `path_query` と同じ。

### 制約
- $0\le u,v\lt N$ 


## lca
```cpp
int lca(int u,int v)
```

頂点 $u,v$ の LCA (最小共通祖先) を返す。

深い方の頂点を heavy path に沿って移動させる、というのを繰り返すことでできる。移動させる回数は根までに通る heavy path の本数以下なので、light edge の本数を考えれば $O(\log N)$

### 制約
- $0\le u,v\le N$ 

### 計算量
- $O(\log N)$


## dist
```cpp
int dist(int u,int v)
```

`lca(u,v)` が求まればそれらの深さから計算できるので、`lca(u,v)` と同じ計算量でできる。

### 制約
- $0\le u,v\le N$ 

### 計算量
- $O(\log N)$


## jump
```cpp
(1) int jump(int v,int k)
(2) int jump(int u,int v,int k)
```

関数名は [Jump on Tree](https://judge.yosupo.jp/problem/jump_on_tree) から。

- (1) 頂点 $v$ から親方向に $k$ 個登った頂点を返す。
- (2) 頂点 $u$ から $v$ の向きに $k$ 個進んだ頂点を返す。

(1) は heavy path に沿って進めていくだけ。heavy path の途中に行きたいときは、heavy path の頂点は euler tour で連続していることを利用すれば適当な計算で求まる。  
(2) は `jump(u,k')` か `jump(v,k')` のどちらかで表せるので、LCA の計算と (1) ができればできる。 

### 制約
- $0\le u,v\lt N$
- (1) $0\le k\le dep[v]$
- (2) $0\le k\le dist(u,v)$

### 計算量
- $O(\log N)$


## 参考

[https://nyaannyaan.github.io/library/tree/heavy-light-decomposition.hpp](https://nyaannyaan.github.io/library/tree/heavy-light-decomposition.hpp)

[https://info.atcoder.jp/entry/algorithm_lectures/heavy_light_decomposition](https://info.atcoder.jp/entry/algorithm_lectures/heavy_light_decomposition)