---
title: modint
documentation_of: modint.hpp
---

mod を取ってくれる

実装の話などはこっちに[https://tau1235.hatenablog.com/entry/2026/09/16/235428](https://tau1235.hatenablog.com/entry/2026/09/16/235428)

## val
```cpp
int val()
```

管理している値の $\bmod M$ の値である $x\ (0\le x\lt M)$ を返す。


## pow
```cpp
modint pow(unsigned long long k)
```

$x^k\bmod M$ を modint 型で返す。

### 制約
- $0\le k$

### 計算量
- $O(\log k)$


## inv
```cpp
modint inv()
```

$x\times x^{-1}\equiv 1\bmod M$ であるような $x^{-1}\bmod M$ を modint 型で返す。  

### 制約
- $\gcd(x,M)=1$ 
- $1\le x\lt M$ 

### 計算量
- $O(\log x)$


## raw
```cpp
modint raw(int x_)
```

そのまま `modint(100)` のようにして初期化する際、値を $\bmod M$ で剰余を取るという操作を行うが、`modint::raw(100)` のようにすることで剰余を取らずに初期化する。

剰余を取る操作 (a%b) がまあまあ重いので、$0\le x\lt M$ であることが分かっていて初期化するときなどに定数倍高速化になる。  
`modint::raw(-1)` を何かしらの演算での単位元などとして使うということもできるらしい(セグ木のモノイドを書くときなど)。


## 演算
```cpp
+x
-x

x++
++x
x--
--x

x+y
x-y
x*y
x/y

x+=y
x-=y
x*=y
x/=y

x==y
x!=y
```

が使える。


## 入出力
```cpp
moint x;
cin>>x;
cout<<x;
```

などが使える。  
`cin>>x` は入力した値で初期化し、`cout<<x` は `x.val()` を出力する。


## 参考

[https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp)

[https://github.com/NyaanNyaan/library/blob/master/modint/modint.hpp](https://github.com/NyaanNyaan/library/blob/master/modint/modint.hpp)

[https://noshi91.hatenablog.com/entry/2019/10/18/182935](https://noshi91.hatenablog.com/entry/2019/10/18/182935)
