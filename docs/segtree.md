---
title: Segment Tree
documentation_of: segtree.hpp
---

抽象化セグメント木  
実装内容は ACL とほぼ同じなのでそっちを見たほうがよい。

管理する列を $a$ とする。

## コンストラクタ
```
(1) SegTree<S,op,e>(int n)
(2) SegTree<S,op,e>(vector<S> v)
```

テンプレート引数として以下の 3 つを渡す。
- モノイド `S`
- 演算 `S op(S a,S b)`
- 単位元 `S e()`

(1) `e()` のみからなる長さ $n$ の列を初期値としてセグメント木を作る。  
(2) 長さ $n=v.size()$ の `vector<S> v` を初期値としてセグメント木を作る。

### 計算量
- $O(n)$


## set
`void set(int x,S val)`

$a_x=val$ として更新する。

### 制約
- $0\le x\lt n$

### 計算量
- $O(\log n)$


## get
`S get(int x)`

$a_x$ を返す。

### 制約
- $0\le x\lt n$

### 計算量
- $O(\log n)$


## prod
`S prod(int l,int r)`

$a_l,a_{l+1},\dots,a_{r-1}$ の総積 $op(a_l,a_{l+1},\dots,a_{r-1})$ を返す。

### 制約
- $0\le l\le r\le n$

### 計算量
- $O(\log n)$


## max_right
`int max_right<f>(int l=0)`

セグ木上の二分探索をする。  

`bool f(S x)` を渡す必要がある。  
$f(a_l),f(a_{l+1}),\dots$ が単調だとしたとき、はじめて `false` となるのを $f(a_r)$ としたとき、 $r$ を返す。もし $f(a_{n-1})$ が `true` なら $r=n$ を返す。

## 制約
- $f$ は $a_l,a_{l+1},\dots$ について単調  
言い換えれば、$f(a_i)$ が `false` ならば $f(a_j)\ (i<j)$ も `false`
- $f(e())$ は `true`
- $0\le l\le n$

## 計算量
- $O(\log n)$