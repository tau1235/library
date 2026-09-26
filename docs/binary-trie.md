---
title: Binary Trie
documentation_of: data-structure/binary-trie.hpp
---

非負整数を管理するとか

ほとんどの操作を計算量 $O(\log M)$ ( 扱う非負整数の最大値を $M$ として ) でできる。  
また、`operator_xor` は $O(1)$ でできる。

## コンストラクタ
```cpp
BinaryTrie<LOG,T>()
```

`2^LOG` 未満の非負整数を管理する Binary Trie を作る。  
管理する非負整数の型 `T` を渡す。`n>>k` で `n` の `k` 桁目が取得できさえすればよく、01 文字列などに無理やり対応させることもできるはず。まだ試してないので上手くいかないかも。  
個数の型を `S` としておいたが、`int` じゃないと駄目なことはまあないと思うので忘れていい。

## add
```cpp
void add(const T &x,S cnt=1)
```

`x` を `cnt` 個追加する。  
`add(x,-1)` などとすることで `erase` の代用もできる。


## erase
```cpp
void erase(const T &x,S cnt=1)
```

`x` を `cnt` 個削除する。

## get_kth
```cpp
T get_kth(S k)
```

小さい方から $k$ 番目の値を返す。重複した値はそれぞれ別物として数えられる。

## max_element
```cpp
T max_element()
```

最大の値を返す。

## min_element
```cpp
T min_element()
```

最小の値を返す。

## count
```cpp
S count(const T &x)
```
$x$ の個数を返す。

## count_less
```cpp
S count_less(const T &x)
```

$x$ 未満の値の個数を返す。

## operate_xor
```cpp
void operate_xor(const T &x)
```

呼ばれた時点で管理している値のすべてを $\rm{xor}\ x$ した値で置き換える。

## 参考

[https://nyaannyaan.github.io/library/data-structure/binary-trie.hpp](https://nyaannyaan.github.io/library/data-structure/binary-trie.hpp)

[https://ei1333.github.io/library/structure/trie/binary-trie.hpp](https://ei1333.github.io/library/structure/trie/binary-trie.hpp)