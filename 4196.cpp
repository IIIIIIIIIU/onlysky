#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int maxtree=maxn<<2|1;

int n,m,f[maxn],deep[maxn],size[maxn],lar[maxn];
int top[maxn],head[maxn],E[maxn<<1|1],V[maxn<<1|1];
int cnt,L[maxtree],R[maxtree],mid[maxtree],tag[maxtree];
int val[maxtree],li[maxn],ri[maxn];

inline void read(int &now)
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

void dfs1(int now,int fa)
{
	f[now]=fa;
	size[now]=1;
	deep[now]=deep[f[now]]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dfs1(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>=size[lar[now]])
				lar[now]=V[i];
		}
}

void dfs2(int now,int chain)
{
	li[now]=++cnt;
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=f[now]&&V[i]!=lar[now])
			dfs2(V[i],V[i]);
	ri[now]=cnt;
}

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
		return;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}

inline void pushdown(int now)
{
	if(tag[now]==1)
	{
		tag[now<<1]=1;
		tag[now<<1|1]=1;
		val[now<<1]=R[now<<1]-L[now<<1]+1;
		val[now<<1|1]=R[now<<1|1]-L[now<<1|1]+1;
	}
	else if(tag[now]==2)
	{
		tag[now<<1]=2;
		tag[now<<1|1]=2;
		val[now<<1]=0;
		val[now<<1|1]=0;
	}
	tag[now]=0;
}

void update(int now,int l,int r,int x)
{
	if(L[now]>=l&&R[now]<=r)
	{
		if(x==1)
		{
			tag[now]=1;
			val[now]=R[now]-L[now]+1;
		}
		else
		{
			tag[now]=2;
			val[now]=0;
		}
		return;
	}
	if(tag[now])
		pushdown(now);
	if(l<=mid[now])
		update(now<<1,l,r,x);
	if(r>mid[now])
		update(now<<1|1,l,r,x);
	val[now]=val[now<<1]+val[now<<1|1];
}

int query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	if(tag[now])
		pushdown(now);
	int res=0;
	if(l<=mid[now])
		res=query(now<<1,l,r);
	if(r>mid[now])
		res+=query(now<<1|1,l,r);
	return res;
}

void SolveUpdate(int x,int d)
{
	while(top[x]!=1)
	{
		update(1,li[top[x]],li[x],d);
		x=f[top[x]];
	}
	update(1,li[top[x]],li[x],d);
}

int SolveQuery(int x)
{
	int res=0;
	while(top[x]!=1)
	{
		res+=query(1,li[top[x]],li[x]);
		x=f[top[x]];
	}
	res+=query(1,li[top[x]],li[x]);
	return res;
}

int main()
{
	read(n);
	for(int i=2;i<=n;i++)
	{
		read(f[i]);
		f[i]++;
		E[++cnt]=head[i];
		V[cnt]=f[i];
		head[i]=cnt;
		E[++cnt]=head[f[i]];
		V[cnt]=i;
		head[f[i]]=cnt;
	}
	cnt=0;
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	read(m);
	char op[20];
	int x;
	while(m--)
	{
		scanf("%s",op);
		read(x);
		x++;
		if(op[0]=='i')
		{
			printf("%d\n",deep[x]-SolveQuery(x));
			SolveUpdate(x,1);
		}
		else
		{
			printf("%d\n",query(1,li[x],ri[x]));
			update(1,li[x],ri[x],2);
		}
	}
	return 0;
}
