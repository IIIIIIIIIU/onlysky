#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
const int maxtree=maxn<<2|1;
struct node
{
	int Max,Min,lval,rval;
	inline node operator+(const node &tmp)const
	{
		node res;
		res.Max=std::max(Max,tmp.Max);
		res.Min=std::min(Min,tmp.Min);
		res.lval=std::max(lval,tmp.lval);
		res.rval=std::max(rval,tmp.rval);
		if(tmp.Max-Min>res.lval)
			res.lval=tmp.Max-Min;
		if(Max-tmp.Min>res.rval)
			res.rval=Max-tmp.Min;
		return res;
	}
};
struct node val[maxtree];
int n,m,deep[maxn],size[maxn],lar[maxn],cnt,head[maxn];
int E[maxn<<1|1],V[maxn<<1|1],id[maxn],top[maxn],f[maxn];
int val_[maxn],back[maxn],L[maxtree],R[maxtree],mid[maxtree];
int tag[maxtree];
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
	deep[now]=deep[fa]+1;
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
	id[now]=++cnt;
	back[cnt]=now;
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=lar[now]&&V[i]!=f[now])
			dfs2(V[i],V[i]);
}
void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		val[now].lval=0;
		val[now].rval=0;
		val[now].Min=val_[back[l]];
		val[now].Max=val_[back[l]];
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	val[now]=val[now<<1]+val[now<<1|1];
}
inline void pushdown(int now)
{
	val[now<<1].Max+=tag[now];
	val[now<<1].Min+=tag[now];
	val[now<<1|1].Max+=tag[now];
	val[now<<1|1].Min+=tag[now];
	tag[now<<1]+=tag[now];
	tag[now<<1|1]+=tag[now];
	tag[now]=0;
}
void update(int now,int l,int r,int x)
{
	if(L[now]>=l&&R[now]<=r)
	{
		tag[now]+=x;
		val[now].Max+=x;
		val[now].Min+=x;
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
node query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	if(tag[now])
		pushdown(now);
	node res;
	bool DID=false;
	if(l<=mid[now])
	{
		res=query(now<<1,l,r);
		DID=true;
	}
	if(r>mid[now])
		if(DID)
			res=res+query(now<<1|1,l,r);
		else
			res=query(now<<1|1,l,r);
	return res;
}
inline int getLca(int x,int y)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
			x=f[top[x]];
		else
			y=f[top[y]];
	if(deep[x]<deep[y])
		return x;
	return y;
}
inline node query(int x,int y)
{
	node res;
	bool DID=false;
	while(top[x]!=top[y])
	{
		if(DID)
			res=query(1,id[top[x]],id[x])+res;
		else
		{
			res=query(1,id[top[x]],id[x]);
			DID=true;
		}
		x=f[top[x]];
	}
	if(DID)
		res=query(1,id[y],id[x])+res;
	else
		res=query(1,id[y],id[x]);
	return res;
}
int Query(int x,int y)
{
	int lca=getLca(x,y);
	node p1=query(x,lca);
	node p2=query(y,lca);
	int t1=std::max(p1.rval,p2.lval);
	return std::max(t1,p2.Max-p1.Min);
}
void add(int x,int y,int z)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			update(1,id[top[x]],id[x],z);
			x=f[top[x]];
		}
		else
		{
			update(1,id[top[y]],id[y],z);
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	update(1,id[x],id[y],z);
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
		read(val_[i]);
	for(int i=1,u,v;i<n;i++)
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
	build(1,1,n);
	read(m);
	int a,b,c;
	while(m--)
	{
		read(a);
		read(b);
		read(c);
		printf("%d\n",Query(a,b));
		add(a,b,c);
	}
	return 0;
}
