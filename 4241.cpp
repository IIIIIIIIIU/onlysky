#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mn=1e5+5;
struct Q{
	int l,r,k,b;
	inline bool operator<(const Q&t)const{
		if(k==t.k)
			return r<t.r;
		return k<t.k;
	}
}q[mn];
int n,m,li[mn],ri[mn],bel[mn],a[mn],b[mn],num;
int ti[mn],st[mn],vi[mn<<1],cnt,T1[mn],T2[mn];
ll s[mn],ans[mn];
inline void in(int &x){
	char c;
	x=0;
	while(!isdigit(c=getchar()));
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
}
inline void A(int x){
	x=a[x];
	--T1[vi[st[x]]];
	--T2[bel[vi[st[x]]]];
	st[x]++;
	++T1[vi[st[x]]];
	++T2[bel[vi[st[x]]]];
}
inline void M(int x){
	x=a[x];
	--T1[vi[st[x]]];
	--T2[bel[vi[st[x]]]];
	st[x]--;
	++T1[vi[st[x]]];
	++T2[bel[vi[st[x]]]];
}
int main(){
	freopen("data.txt","r",stdin);
	in(n);
	in(m);
	int bs=std::sqrt(n);
	for(int i=1;i<=n;i++){
		bel[i]=i/bs+1;
		in(a[i]);
		b[++num]=a[i];
	}
	for(int i=1;i<=m;i++){
		in(q[i].l);
		in(q[i].r);
		q[i].b=i;
		q[i].k=bel[q[i].l];
	}
	std::sort(q+1,q+m+1);
	std::sort(b+1,b+num+1);
	num=std::unique(b+1,b+num+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=std::lower_bound(b+1,b+num+1,a[i])-b;
		ti[a[i]]++;
	}
	for(int i=1,x=0;i<=num;i++){
		for(int v=1;v<=ti[i];v++){
			++x;
			s[x]=1LL*b[i]*v;
		}
	}
	std::sort(s+1,s+n+2);
	int N=std::unique(s+1,s+n+2)-s-1;
	for(int i=1;i<=num;i++){
		st[i]=++cnt;
		vi[cnt]=1;
		for(int v=1;v<=ti[i];v++){
			++cnt;
			vi[cnt]=std::lower_bound(s+1,s+N+1,1LL*b[i]*v)-s;
		}
	}
	bs=std::sqrt(N);
	int tt=0;
	for(int i=1;i<=N;i++){
		bel[i]=i/bs+1;
		if(!li[bel[i]])
			li[bel[i]]=i;
		ri[bel[i]]=i;
		tt=bel[i];
	}
	T1[1]=T2[1]=num;
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(r<q[i].r)
			A(++r);
		while(r>q[i].r)
			M(r--);
		while(l>q[i].l)
			A(--l);
		while(l<q[i].l)
			M(l++);
		for(int v=tt;v>=1;v--)
			if(T2[v]){
				for(int e=ri[v];e>=li[v];e--){
					if(T1[e]){
						ans[q[i].b]=s[e];
						break;
					}
				}
				break;
			}
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
