#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll INF=1e18;
const ll maxn=1e6+5;
const ll maxtree=maxn<<2|1;

ll n,m,L[maxtree],R[maxtree],mid[maxtree],val[maxtree];
ll tag[maxtree],has[maxtree],deep[maxn],f[maxn],size[maxn];
ll lar[maxn],top[maxn],li[maxn],ri[maxn],tval[maxn],root;
ll cnt,head[maxn],E[maxn<<1|1],V[maxn<<1|1],back[maxn];

inline void read(ll &now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

void build(ll now,ll l,ll r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		val[now]=tval[l];
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	val[now]=std::min(val[now<<1],val[now<<1|1]);
}

inline void pushdown(ll now)
{
	has[now]=false;
	has[now<<1]=has[now<<1|1]=true;
	val[now<<1]=val[now<<1|1]=tag[now];
	tag[now<<1]=tag[now<<1|1]=tag[now];
}

void update(ll now,ll l,ll r,ll x)
{
	if(L[now]>=l&&R[now]<=r)
	{
		val[now]=x;
		tag[now]=x;
		has[now]=true;
		return;
	}
	if(has[now])
		pushdown(now);
	if(l<=mid[now])
		update(now<<1,l,r,x);
	if(r>mid[now])
		update(now<<1|1,l,r,x);
	val[now]=std::min(val[now<<1],val[now<<1|1]);
}

ll query(ll now,ll l,ll r)
{
	if(l>r)
		return INF;
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	if(has[now])
		pushdown(now);
	ll res,DID=false;
	if(l<=mid[now])
	{
		res=query(now<<1,l,r);
		DID=true;
	}
	if(r>mid[now])
	{
		if(DID)
			res=std::min(res,query(now<<1|1,l,r));
		else
			res=query(now<<1|1,l,r);
	}
	return res;
}

void dfs1(ll now,ll fa)
{
	f[now]=fa;
	size[now]=1;
	deep[now]=deep[fa]+1;
	for(ll i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dfs1(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>size[lar[now]])
				lar[now]=V[i];
		}
}

void dfs2(ll now,ll chain)
{
	li[now]=++cnt;
	top[now]=chain;
	back[cnt]=now;
	if(lar[now])
		dfs2(lar[now],chain);
	for(ll i=head[now];i!=0;i=E[i])
		if(V[i]!=lar[now]&&V[i]!=f[now])
			dfs2(V[i],V[i]);
	ri[now]=cnt;
}

void update(ll x,ll y,ll z)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			update(1,li[top[x]],li[x],z);
			x=f[top[x]];
		}
		else
		{
			update(1,li[top[y]],li[y],z);
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	update(1,li[x],li[y],z);
}

inline ll up(ll x,ll t)
{
	while(deep[top[x]]>t)
		x=f[top[x]];
	return back[li[x]-(deep[x]-t)];
}

ll query(ll x)
{
	if(x==root)
		return query(1,1,n);
	if(li[x]>=li[root]&&ri[x]<=ri[root])
		return query(1,li[x],ri[x]);
	if(ri[x]<li[root]||li[x]>ri[root])
		return query(1,li[x],ri[x]);
	ll t=up(root,deep[x]+1),res=INF;
	if(li[t]>1)
		res=std::min(res,query(1,1,li[t]-1));
	if(ri[t]<n)
		res=std::min(res,query(1,ri[t]+1,n));
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	for(ll i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	cnt=0;
	dfs1(1,0);
	dfs2(1,1);
	for(ll i=1;i<=n;i++)
		read(tval[li[i]]);
	build(1,1,n);
	read(root);
	ll op,l,r,x;
	while(m--)
	{
		read(op);
		if(op==1)
			read(root);
		else if(op==2)
		{
			read(l);
			read(r);
			read(x);
			update(l,r,x);
		}
		else if(op==3)
		{
			read(x);
			printf("%lld\n",query(x));
		}
	}
	return 0;
}
