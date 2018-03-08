#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;
const int maxn=2e5+5;
const int maxtree=maxn<<2|1;

int n,m,ai[maxn],L[maxtree],R[maxtree],mid[maxtree];

ll val[maxtree],tag[maxtree];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		x=x*x%mod;
		e>>=1;
	}
	return res;
}

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	tag[now]=1;
	if(l==r)
	{
		if(l==n)
			val[now]=1;
		else
			val[now]=2*poww(3,n-l-1)%mod;
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	val[now]=(val[now<<1]+val[now<<1|1])%mod;
}

inline void pushdown(int now)
{
	val[now<<1]=val[now<<1]*tag[now]%mod;
	val[now<<1|1]=val[now<<1|1]*tag[now]%mod;
	tag[now<<1]=tag[now<<1]*tag[now]%mod;
	tag[now<<1|1]=tag[now<<1|1]*tag[now]%mod;
	tag[now]=1;
}

void update(int now,int l,int r,int x)
{
	if(L[now]>=l&&R[now]<=r)
	{
		val[now]=val[now]*x%mod;
		tag[now]=tag[now]*x%mod;
		return;
	}
	if(tag[now]!=1)
		pushdown(now);
	if(l<=mid[now])
		update(now<<1,l,r,x);
	if(r>mid[now])
		update(now<<1|1,l,r,x);
	val[now]=(val[now<<1]+val[now<<1|1])%mod;
}

int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai[i]);
		update(1,i,n,ai[i]%mod);
	}
	int pos,x;
	while(m--)
	{
		scanf("%d%d",&pos,&x);
		update(1,pos,n,poww(ai[pos],mod-2)*x%mod);
		ai[pos]=x;
		printf("%lld\n",val[1]);
	}
	return 0;
}
