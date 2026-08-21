// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_range_sum

#include<bits/stdc++.h>
using namespace std;

#include"segtree.hpp"

using ll=long long;
ll op(ll a,ll b){return a+b;}
ll e(){return 0LL;}

int main(){
	int n,q;
	cin>>n>>q;
	SegTree<ll,op,e> seg(n);
	for (int i=0;i<n;i++){
		int a;
		cin>>a;
		seg.set(i,a);
	}
	while (q--){
		int t;
		cin>>t;
		if (t==0){
			int p,x;
			cin>>p>>x;
			seg.set(p,seg.get(p)+x);
		}
		if (t==1){
			int l,r;
			cin>>l>>r;
			cout<<seg.prod(l,r)<<endl;
		}
	}
}
