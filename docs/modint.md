---
title: modint
documentation_of: modint.hpp
---

mod を良い感じに取ってくれる

## メモ
ほとんどの場合で、atcoder::modint から置き換え可能だと思う

内部で値を持つのを int で持つことで long long で持つより省メモリ

`modint& operator+=` で & をつけることで、`(x+=1)+=1;` で `x+=2;` みたいなことができる

`friend modint operator+` と `modint operator+` では、`(int)1+(modint)2` とかにも対応できる方が前者、対応できないのが後者

`operator++()` が `++x`  
`operator++(int)` `x++`  
https://learn.microsoft.com/ja-jp/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170

`cin>>x;` `cout<<x;` とかに対応してる
初めて書いた

x を private にするべきなのかは、よくわからない

## inv
$ax \equiv 1\pmod M$ を満たす $a$ (すなわち $x^{-1}$) を $O(\log M)$ で求める。  
ただし、$\gcd(x,M)=1$ でなければいけない。そうでない場合はそもそも $x$ の逆元 $x^{-1} \pmod M$ は存在しない。  
```cpp
modint inv()const{
  int a=mod,b=x,u=0,v=1;
  while (b){
    int q=a/b;
    swap(a-=q*b,b);
    swap(u-=q*v,v);
  }
  return modint(u);
}
```
↑ これで求めることができるというのは知ってたけど、なぜ求められるのかをあんまり分かってなかった。noshi91 さんのを見てようやく理解できた気がする。  

一応自分なりに考えたこと  
$s\equiv tx\pmod M$ のような形の式について考える。  
$s_1\equiv t_1x,s_2\equiv t_2x$ という 2 つの式があるとき、適当な整数 $k$ を取って式を足し引きすることで $(s_1-ks_2)\equiv (t_1-kt_2)x$ という同じ形の式を作れる。  
$s$ についてユークリッドの互除法をしていく感じで最終的に $s=1\equiv tx$ という式を作ることができるので、そのときの $t$ が $x^{-1}\pmod M$ になっている。  

より詳しく書けば、  
$s_1=M,t_1=0$ とした $M\equiv 0\times x$  
$s_2=x,t_2=1$ とした $x\equiv 1\times x$  
という 2 つの式を初期値とする。ここで、  
$s_n\equiv t_n\times x$  
$s_{n+1}\equiv t_{n+1}\times x$  
が分かっていて $s_n=qs_{n+1}+r(0\le r\lt s_n)$ と書けるとき、$k=q$ として足し引きすることで  
$(s_n-qs_{n+1})\equiv (t_n-qt_{n+1})x$ という式が得られる。  
$s_{n+2}=s_n-qs_{n+1}=r$  
$t_{n+2}=t_n-qt_{n+1}$  
というような漸化式のようなものを考えれば、$s_n$ が単調減少であり、$s_n$ の連続した 2 項をずらしながら見ていくことがユークリッドの互除法に対応していることなどが分かる。ユークリッドの互除法で $s_n=\gcd(M,x)=1$ となったときの $t_n$ が $x^{-1}\pmod M$ になっている。 

結局、さっきのコードで求まる理由としては $s_n,t_n$ の連続した 2 項をそれぞれ持ってずらしていっていると見ることができるからと言える。  
$(a,b)$ が $(s_n,s_{n+1})$ を、$(u,v)$ が $(t_n,t_{n+1})$ を表していて、一回のループで $(a,b),(u,v)$ がそれぞれ $(s_{n+1},s_{n+2}),(t_{n+1},t_{n+2})$ と変化していることが分かる。
$b=0$ のとき $(s_n,s_{n+1})=(1,0)$ であるので `while(b)` となっていること、$t_n=u$ を返すようになっていることが分かる。  

そう考えると、
```cpp
modint inv()const{
  int a=mod,b=x,u=0,v=1;
  while (b>1){
    int q=a/b;
    swap(a-=q*b,b);
    swap(u-=q*v,v);
  }
  return modint(v);
}
```
とした方が 1 ループ減るし、書き方も自然な気がしてくる。が、下記の $\gcd(x,M)\ne 1$ である場合には使えなくなるので微妙かも。

一応、$\gcd(x,M)=g\ne 1$ である場合でも $ax\equiv g\pmod M$ である $a$ を返す、というようになっているが、ほぼ使わないと思う。

オーバーフローについてもちょっと考えようとしたけど、よくわからなかった  
軽く調べたらこういうのがあった  
この場合も同じようなことが言えるのかもしれない？
https://satashun.hatenablog.com/entry/2019/12/30/231319


$M$ が素数 $P$ である場合はフェルマーの小定理から $x^{-1} \equiv x^{P-2}$ であることが分かるので、繰り返し二乗法で $O(\log M)$ になる。繰り返し二乗法では計算回数が $x$ の値に関わらずほぼ一定になるのに対し、ユークリッドの互除法の方では $x$ の値によって高速になるケースがあるなどのメリットがある(気がする)。

## 参考
https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp

https://github.com/NyaanNyaan/library/blob/master/modint/modint.hpp

https://noshi91.hatenablog.com/entry/2019/10/18/182935
