---
title: 永続セグメント木
documentation_of: data-structure/persistent-segtree.hpp
---

動的セグメント木を永続化したもの。  
ポインタ木による実装。

使い方も基本的には普通のセグメント木と同じだが、$t$ を指定することで、どの時点のセグメント木に対して操作をするかを指定できる。

$t$ という変数が表す意味については、時刻 $t$ の状態、のイメージで書いている。ポインタとして木 $t$ を渡して操作をする、というような実装もよく見るが自分はそうしてない。できればポインタをデータ構造の外で扱いたくないという理由もちょっとはあるが、まあ好みの問題。

初期化を除いて、新たな状態を作成するごとに空間計算量は $O(\log n)$

## コンストラクタ
```cpp
(1) PersistentSegmentTree<S,op,e>(ll n)
(2) PersistentSegmentTree<S,op,e>(vector<S> v)
```

テンプレート引数は通常のセグメント木と同じ  
このときの状態を状態 $0$ とする。

- (1) 全ての要素が `e()` である長さ $n$ の列 $a$ を初期値としてセグメント木を作る。
- (2) $a=v$ を初期値としてセグメント木を作る。

### 制約
- $1\le n\le 2^{62}$

### 計算量
- (1) $O(1)$
- (2) $O(n)$


## set
```cpp
(1) void set(int t,ll p,S x)
(2) void set(ll p,S x)
```

- (1) 状態 $t$ のセグメント木に対し、$a_p=x$ に更新した後の状態を最新の状態として作成する。
- (2) 関数を呼んだ時点での最新の状態に対して (1) をする。

### 制約
- $t$ は $0$ 以上で、状態 $t$ のセグメント木が既に存在する
- $0\le p\lt n$

### 計算量
- $O(\log n)$


## get
```cpp
(1) S get(int t,ll p)
(2) S get(ll p)
```

- (1) 状態 $t$ のセグメント木における $a_p$ を返す。
- (2) 関数を呼んだ時点での最新の状態に対して (1) をする。

### 制約
- $t$ は $0$ 以上で、状態 $t$ のセグメント木が既に存在する
- $0\le p\lt n$

### 計算量
- $O(\log n)$


## prod
```cpp
(1) S prod(int t,ll l,ll r)
(2) S prod(ll l,ll r)
```

- (1) 状態 $t$ のセグメント木において、$a_l,a_{l+1},\dots,a_{r-1}$ の総積 $op(a_l,a_{l+1},\dots,a_{r-1})$ を返す。
- (2) 関数を呼んだ時点での最新の状態に対して (1) をする。

### 制約
- $t$ は $0$ 以上で、状態 $t$ のセグメント木が既に存在する
- $0\le l\le r\le n$

### 計算量
- $O(\log n)$


## max_right
```cpp
(1) ll max_right<g>(int t,ll l)
(2) ll max_right<g>(ll l)
```

セグ木上の二分探索をする。  
工夫すれば新しくノードを作らなくてもよくなるはずだけど、してないので $O(\log n)$ 個のノードを追加で作る。

`bool g(S x)` を渡す必要がある。  
- (1) 状態 $t$ において、$g(op(a\lbrack l,r)))\ (l\le r)$ が単調だとしたとき、`true` となる最大の $r\ (\ge l)$ を返す。$g(op(a\lbrack l,l)))=g(e())$ が `true` であることを必要とするので、$r$ は必ず存在する。
- (2) 関数を呼んだ時点での最新の状態に対して (1) をする。

## 制約
- $t$ は $0$ 以上で、状態 $t$ のセグメント木が既に存在する
- $g$ は $r$ について $g(op(a\lbrack l,r)))$ が単調  
言い換えれば、$g(op(a\lbrack l,r)))$ が `false` ならば $g(op(a\lbrack l,r+1)))$ も `false`
- $g(e())$ は `true`
- $0\le l\lt n$

## 計算量
- $O(\log n)$


## max_right_pair
```cpp
ll max_right_pair<g>(int t1,int t2,ll l)
```

`max_right` の派生で、状態を 2 つ渡し、その 2 つの状態から計算できる何かしらについての二分探索を行う。  
区間クエリで累積和っぽいことを考えて使うことが多そう。 
使う例としては、[LCのこれ](https://judge.yosupo.jp/problem/range_kth_smallest) があるが、他の例を知らない。コンテスト中とかに書こうとすると頭を壊しそうだから一応ライブラリ化しておいた。

`bool g(S x,S y)` を渡す必要がある。  
状態 $t_1,t_2$ における $a$ をそれぞれ $a_1,a_2$ とする。$g( op(a_1\lbrack l,r)) , op(a_2\lbrack l,r)) )\ (l\le r)$ が単調だとしたとき、`true` となる最大の $r\ (\ge l)$ を返す。$g( op(a_1\lbrack l,l)) , op(a_2\lbrack l,l)) )=g(e(),e())$ が `true` であることを必要とするので、$r$ は必ず存在する。

## 制約
- $t_1,t_2$ は $0$ 以上で、状態 $t_1,t_2$ のセグメント木が既に存在する
- $g$ は $r$ について $g( op(a_1\lbrack l,r)) , op(a_2\lbrack l,r)) )$ が単調  
言い換えれば、$g( op(a_1\lbrack l,r)) , op(a_2\lbrack l,r)) )$ が `false` ならば $g( op(a_1\lbrack l,r+1)) , op(a_2\lbrack l,r+1)) )$ も `false`
- $g(e(),e())$ は `true`
- $0\le l\lt n$

## 計算量
- $O(\log n)$


## copy_range
```cpp
void copy_range(int to,int from,ll l,ll r)
```

区間のコピーをする。  
詳しく言えば、状態 `to` に対し区間 $\lbrack l,r)$ の各要素を状態 `from` の区間 $\lbrack l,r)$ の各要素たちでそれぞれ置き換える操作を行った後の状態を最新の状態として作成する。

### 制約
- `from` は $0$ 以上で、状態 `from` のセグメント木が既に存在する
- `to` は $0$ 以上で、状態 `to` のセグメント木が既に存在する
- $0\le l\le r\le n$

### 計算量
- $O(\log n)$


## prev
```cpp
int prev()
```

この関数を呼んだ時点での最新の状態が何番であるかを返す。


## reset
```cpp
void reset()
```

`PersistentSegmentTree` によって作成した Node 数が `NODES`($10^7$ としている) を超えた場合、壊れる。  
この関数を呼ぶことで今まで作成した Node をすべて削除(実際には削除しないが)し、初期化する。マルチテストケースとかのケース間で使う場合などを想定している。


## 参考
[https://info.atcoder.jp/entry/algorithm_lectures/persistent_segment_tree](https://info.atcoder.jp/entry/algorithm_lectures/persistent_segment_tree)

[https://maspypy.github.io/library/ds/segtree/dynamic_segtree.hpp](https://maspypy.github.io/library/ds/segtree/dynamic_segtree.hpp)