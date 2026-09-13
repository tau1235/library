---
title: modint
documentation_of: modint.hpp
---

mod を良い感じに取ってくれる

## メモ

普段使う範囲では atcoder::modint から置き換え可能だと思う

内部で値を持つのを int で持つことで long long で持つより省メモリ

`modint& operator+=` で & をつけることで、`(x+=1)+=1;` で `x+=2;` みたいなことができる

`friend modint operator+` と `modint operator+` では、`(int)1+(modint)2` とかにも対応できる方が前者、対応できないのが後者

`operator++()` が `++x`  
`operator++(int)` `x++`  
[これ関連のリンク](https://learn.microsoft.com/ja-jp/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170)

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
↑ これで求めることができるというのは知ってたけど、なぜ求められるのかをあんまり分かってなかった。ようやく理解できた気がするので一応なんか書いておく。  

整数 $x\ (0<x<M)$ は定数とし、$x^{-1}$ を求めることにする。
$s\equiv tx\pmod M$ のような形の式について考える。  
$s_1\equiv t_1x,s_2\equiv t_2x$ という 2 つの式があるとき、適当な整数 $k$ を取って式を足し引きすることで $(s_1-ks_2)\equiv (t_1-kt_2)x$ という同じ形の式を作れる。  
$s$ についてユークリッドの互除法をしていく感じで最終的に $s=1\equiv tx$ という式を作ることができるので、そのときの $t$ が $x^{-1}\pmod M$ になっている。  

より詳しく書けば、  
$s_1=M,t_1=0$ とした $M\equiv 0\times x$  
$s_2=x,t_2=1$ とした $x\equiv 1\times x$  
という 2 つの式を初期値とする。ここで、  
$s_n\equiv t_n\times x$  
$s_{n+1}\equiv t_{n+1}\times x$  
が分かっていて $s_n=q_n s_{n+1}+r_n\ (q_n=\lfloor\frac{s_n}{s_{n+1}}\rfloor,r_n=(s_n \bmod s_{n+1}))$ と書けるとき、$k=q_n$ として足し引きすることで  
$(s_n-qs_{n+1})\equiv (t_n-q_n t_{n+1})x$ という式が得られる。  
$s_{n+2}=s_n-q_n s_{n+1}=r_n$   
$t_{n+2}=t_n-q_n t_{n+1}$  
というような漸化式のようなものを考えれば、$s_n$ の連続した 2 項をずらしながら見ていくことがユークリッドの互除法に対応していることなどが分かる。  
ユークリッドの互除法が進んでいくことで $s_n=\gcd(M,x)=1$ となったときの $t_n$ が $x^{-1}\pmod M$ になっている。 

例として、$M=23,x=18$ であるときに $x^{-1}\pmod M$ を求めることを考えてみます。  
$s_1=M=23,\ t_1=0,\ s_2=x=18,\ t_2=1$ で、    

$(1)\ 23\equiv 0\times18$  
$(2)\ 18\equiv 1\times18$  
$(3)\ 5\equiv -1\times18\ \lbrace(1)-1\times(2)\rbrace$  
$(4)\ 3\equiv 4\times18\ \lbrace(2)-3\times(3)\rbrace$  
$(5)\ 2\equiv -5\times18\ \lbrace(3)-1\times(4)\rbrace$  
$(6)\ 1\equiv 9\times18\ \lbrace(4)-1\times(5)\rbrace$  
$(7)\ 0\equiv -23\times18\ \lbrace(5)-2\times(6)\rbrace$  

のように進み、(6) の $1\equiv 9\times18$ から、$x^{-1}=9$ が分かる、という感じ。  

結局、さっきのコードで求まる理由としては、今説明した方法での $s_n,t_n$ の連続した 2 項をそれぞれ持ち、見る項をずらしていっていると捉えられるから、と言える。(これ以外の解釈もあるかもしれないから一応濁してるけどさすがにないと思う)  
$(a,b)$ が $(s_n,s_{n+1})$ を、$(u,v)$ が $(t_n,t_{n+1})$ を表していて、一回のループで $(a,b),(u,v)$ がそれぞれ $(s_{n+1},s_{n+2}),(t_{n+1},t_{n+2})$ と変化していることが分かる。  
また、 $a,b,u,v$ の初期値がそれぞれ $s_1,s_2,t_1,t_2$ と対応していることも分かる。  
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
とした方が 1 ループ減るし、書き方も自然な気がしてくる。が、下記の $\gcd(x,M)\ne 1$ である場合には使えなくなるので微妙かも？

一応、$\gcd(x,M)=g\ne 1$ である場合でも $ax\equiv g\pmod M$ である $a$ を返す、というようになっているが、ほぼ使わないと思う。

$M$ が素数 $P$ である場合はフェルマーの小定理から $x^{-1} \equiv x^{P-2}$ であることが分かるので、繰り返し二乗法で $O(\log M)$ になる。繰り返し二乗法では計算回数が $x$ の値に関わらずほぼ一定になるのに対し、ユークリッドの互除法の方では $x$ の値によって高速になるケースがあるなどのメリットがある(気がする)。

### オーバーフローとか

ところで、拡張ユークリッドの互除法には主に 2 つのパターンがあって、再帰するのと再帰しないの (さっきまで扱っていたもの) がある。(厳密にはさっき説明したものは拡張ユークリッドの互除法そのものというよりはその省略版ではあるが、$M$ の係数も持つようにすれば拡張ユークリッドの互除法と同じことなので)  
これを実装したときにオーバーフロー周りの話が気になったので検索してみたが、再帰の方についてはいくつか見つかったものの非再帰の方についての話がほぼ見つからなかった。困ったので自分で書いてみた。

再帰で書いたコード

```cpp
pair<int,int> extgcd(int a,int b){
  if (b==0) return {1,0};
  auto [y,x]=extgcd(b,a%b);
  y-=a/b*x;
  return {x,y};
}
```

[再帰の方の話1](https://satashun.hatenablog.com/entry/2019/12/30/231319) [再帰の方の話2](https://teratail.com/questions/176282)  

非再帰で実装した以下のコードについて考えていく。

```cpp
modint inv()const{
  int a=mod,b=x,u=0,v=1;
  //assert(a*abs(v)+b*abs(u)==mod);//<1>
  //assert(0<=a&&a<=mod);//<4>
  //assert(abs(u)<=mod/2);//<5>
  while (b){
    int q=a/b;
    //assert(abs(q*b)<=mod);//<2>
    //assert(abs(q*v)<=mod);//<3>
    swap(a-=q*b,b);
    swap(u-=q*v,v);
    //assert(a*abs(v)+b*abs(u)==mod);//<1>
    //assert(0<=a&&a<=mod);//<4>
    //assert(abs(u)<=mod/2);//<5>
  }
  //assert(abs(b)<=mod);//<4>
  //assert(abs(u)<=mod/2);//<5>
  //assert(abs(v)==mod);//<6>
  return modint(u);
}
```

さっき説明していたコードにいくつか assert 文を追加してコメントアウトした感じになっているが、これらの assert 文は成り立つことが最終的に言える。  

改めて、コード中に出てくる値などを確認しておく。  
$s_1=M,\ s_2=x$  
$t_1=0,\ t_2=1$  
$q_i:=\lfloor\frac {s_i}{s_{i+1}}\rfloor$  
`while(b)` の中の処理をする回数を $N$ とする。さっき書いた例の場合では $N=5$  
$s_{i+2}:=s_i-q_i s_{i+1}\ (1\le i\le N)$  
$t_{i+2}:=t_i-q_i t_{i+1}\ (1\le i\le N)$  
$t_{N+1}=x^{-1}$

assert 文の中身を $s_i,t_i$ などを使って表すと、以下の 6 つのような形になる。  
<1> $s_i|t_{i+1}|+s_{i+1}|t_i|=M\ (1\le i\le N+1)$  
<2> $|q_i s_{i+1}|\le M\ (1\le i\le N)$  
<3> $|q_i t_{i+1}|\le M\ (1\le i\le N)$  
<4> $0\le s_i\le M\ (1\le i\le N+2)$  
<5> $|t_i|\le \frac M 2\ (1\le i\le N+1)$  
<6> $|t_{N+2}|=M$  
これらを示す。

<4> はユークリッドの互除法を考えれば分かるので省略。

一番謎なのは <1> だと思う。というかこれさえ示せればほぼ終わりみたいな感じ。  
これを示す前に、いくつか示すことがある。  

> #### 補題 1
> $t_i$ の符号は反転する  
> より厳密には、$i$ が奇数のとき、$t_i\le0$ で、偶数のとき $t_i\gt0$  

帰納法で示す。$i=1,2$ のとき、$t_1=0\le0,t_2=1\gt0$ で成り立つ。  
(1) より、$t_{i+2}=t_i-q_i t_{i+1}=t_i+q_i\times(-t_{i+1})$ で、$t_i,t_{i+1}$ は符号が反転していることを仮定すれば、$q_i>0$ なので、$t_i,-t_{i+1}$ は符号が同じである。なので $t_{i+2}$ は $t_i$ と符号が同じであることが言えるので、補題 1 が示せた。  
補題 1 から、以下の補題 2 もすぐに分かる。

> #### 補題 2
> $|t_{i+2}|=|t_i|+q_i|t_{i+1}|$ 

補題 1,2 が分かったので、<1> を示せる。  

<1> を帰納法で示す。  
まず、$s_1|t_2|+s_2|t_1|=M\times1+x\times0=M$  なので $i=1$ のとき成り立つ。  

$$\begin{split}
&s_{i+1}|t_{i+2}|+s_{i+2}|t_{i+1}|\\
=\ &s_{i+1}(|t_i|+q_i|t_{i+1}|)+(s_i-q_i s_{i+1})|t_{i+1}|\\
=\ &s_{i+1}|t_i|+q_is_{i+1}|t_{i+1}|+s_i|t_{i+1}|-q_is_{i+1}|t_{i+1}|\\
=\ &s_i|t_{i+1}|+s_{i+1}|t_i|\\
=\ &M
\end{split}$$

1, 2 行目間では $t_{i+2},s_{i+2}$ の定義を、4, 5 行目間では帰納法の仮定を用いている。  
よって、帰納法により <1> を示せた。  

<5> を示す。  
$s_i$ はユークリッドの互除法と同じことをしているから、$s_{N+2}=0,\ s_{N+1}=\gcd(M,x)=1,\ s_i\ge2\ (1\le i\le N)$ が分かる。  
$1\le i\le N$ について $s_{i+1}\ge 1,|t_i|\ge 0$ だから、<1> を使えば、$s_i|t_{i+1}|\le s_i|t_{i+1}|+s_{i+1}|t_i|=M$ となる。  
$s_i\ge 2\ (1\le i\le N)$ だったことと、この $s_i|t_{i+1}|\le M$ を合わせれば $|t_{i+1}|\le \frac M 2$ となるので、添え字をずらして $|t_i|\le \frac M 2\ (2\le i\le N+1)$ となる。  
$t_1=0$ も合わせれば <5> $|t_i|\le \frac M 2\ (1\le i\le N+1)$ が示せた。  

<6> を示す。  
<1> で $i=N+1$ とすれば、$s_{N+1}|t_{N+2}|+s_{N+2}|t_{N+1}|=M$ であり、$s_{N+1}=1,s_{N+2}=0$ だから $1\times|t_{N+2}|+0\times|t_{N+1}|=|t_{N+2}|=M$ なので示せた。  
<5>,<6> をまとめて $|t_i|\le M\ (1\le i\le N+2)$ とするだけでもオーバーフローしないことを示したいだけなら十分。  

<2>,<3> を示す。  
補題 2 から  
$|t_{i+2}|=|t_i|+q_i|t_{i+1}|$  
$q_i|t_{i+1}|=|t_{i+2}|-|t_i|$  

$1\le i\le N-1$ のとき、$|t_i|,|t_{i+2}|\le \frac M 2$ であるから $q_i|t_{i+1}|\le \frac M 2$  
$i=N$ のとき $q_N|t_{N+1}|=|t_{N+2}|-|t_N|$ で、$M=|t_{N+2}|\ge |t_N|$ なので $q_N|t_{N+1}|\le M$   
$q_i>0$ だから $q_i|t_{i+1}|=|q_it_{i+1}|\le M\ (1\le i\le N)$ として <3> が示せた。  
$i=N$ のときだけ $\frac M 2$ で抑えられていないのが気になるが、前に挙げた例の場合でも $\frac M 2$ より大きくなっているのでそもそも成り立たないことが分かる。

<2> も同様に $q_i s_{i+1}=s_i-s_{i+2}\le M$ となるので略。まあ <2> に関してはユークリッドの互除法を考えるだけなのでかなり自明かも。  

これで全て示せたので、$M$ が int に収まるならこのコードではオーバーフローしないことが分かった。これで心置きなく modinv を求めることができる。やったね。

一応副産物もあって、このコードで得られる $x^{-1}$ (最終的な $u$ の値という意味で) は $-\frac M 2\le x^{-1}\le \frac M 2$ であるから、以下のコードも正当であることが言える。

```cpp
modint inv()const{
  int a=mod,b=x,u=0,v=1;
  while (b){
    int q=a/b;
    swap(a-=q*b,b);
    swap(u-=q*v,v);
  }
  if (u<0) u+=mod;
  return modint::raw(u);
}
```

初期化の際の剰余がいらなくなるのでちょっと速くなるかも？多分誤差だと思う。

### おまけ 1

今回は $x$ の係数にしか興味がなかったが、$M$ の係数についても同じことを考えれば評価ができるはずなので、拡張ユークリッドの互除法の値の評価をすることもできるはず。面倒だからやらない。  

[再帰の方の話2](https://teratail.com/questions/176282) などに書いてあるが、再帰の方で拡張ユークリッドの互除法をすると最適？な解が求められるらしい。この感じだと非再帰の場合でも最適な解が求まっているはず。というかどっちの実装でも全く同じ解が求まるのかも？

### おまけ 2

$M$ を固定したとき、 $N$ が最大値をとるような $x$ は何か？  

ちなみに、$M=998244353$ の場合 $N=36$ で $x=579320910,616131005,616830068,620239463$ で最大値を取るらしい。これは愚直を数分間くらい実行して求めた。  
$\mathrm{Fib}_{36}=9227465$ なのでフィボナッチ数による上界よりはかなり少なめ。

愚直にやる以上にいい方法あるかな？

## 参考

[https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp)

[https://github.com/NyaanNyaan/library/blob/master/modint/modint.hpp](https://github.com/NyaanNyaan/library/blob/master/modint/modint.hpp)

[https://noshi91.hatenablog.com/entry/2019/10/18/182935](https://noshi91.hatenablog.com/entry/2019/10/18/182935)
