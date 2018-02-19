#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
typedef long long ll;
const int maxn=1e5+5;
const int maxtree=maxn<<2|1;
struct node
{
	bool has;
	ll a,b,Min,len;
	node()
	{
		has=false;
		Min=123456789123456789LL;
	}
	void update()
	{
		if(has)
			Min=std::min(b,a*len+b);
	}
};
struct node seg[maxtree];
int n,m,head[maxn],E[maxn<<1],V[maxn<<1],cnt;
int deep[maxn],L[maxtree],R[maxtree],mid[maxtree];
int id[maxn],size[maxn],lar[maxn],f[maxn],top[maxn];
int back[maxn];
ll dis[maxn],val[maxtree],W[maxtree],step[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
inline void read(ll &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
void dfs1(int now,int fa)
{
	f[now]=fa;
	size[now]=1;
	deep[now]=deep[fa]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dis[V[i]]=dis[now]+W[i];
			step[V[i]]=W[i];
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
		if(V[i]!=f[now]&&V[i]!=lar[now])
			dfs2(V[i],V[i]);
}
void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	val[now]=seg[now].Min;
	seg[now].len=dis[back[r]]-dis[back[l]];
	if(l==r)
		return;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}
inline int getlca(int x,int y)
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
inline real getpoint(real a1,real b1,real a2,real b2)
{
	if(a1==a2)
		return -1;
	return (b2-b1)/(a1-a2);
}
void pushdown(int now,ll a,ll b)
{
	if(!seg[now].has)
	{
		seg[now].has=true;
		seg[now].a=a;
		seg[now].b=b;
		seg[now].update();
		val[now]=std::min(val[now],seg[now].Min);
		return;
	}
	if(L[now]==R[now])
	{
		if(b<seg[now].b)
		{
			seg[now].b=b;
			seg[now].a=a;
			seg[now].update();
		};
		val[now]=std::min(val[now],seg[now].Min);
		return;
	}
	real p=getpoint(seg[now].a,seg[now].b,a,b);
	if(p<0||p>seg[now].len)
	{
		real Mid=seg[now].len;
		Mid/=2;
		if(Mid*a+b<Mid*seg[now].a+seg[now].b)
		{
			seg[now].b=b;
			seg[now].a=a;
			seg[now].update();
			val[now]=std::min(val[now],seg[now].Min);
		}
		return;
	}
	else
	{
		ll tmp=seg[now<<1].len;
		if(p<=tmp)
		{
			if(b>seg[now].b)
			{
				pushdown(now<<1,seg[now].a,seg[now].b);
				seg[now].a=a;
				seg[now].b=b;
			}
			else
				pushdown(now<<1,a,b);
		}
		else
		{
			if(b<seg[now].b)
			{
				pushdown(now<<1|1,seg[now].a,seg[now].b+(seg[now].len-seg[now<<1|1].len)*seg[now].a);
				seg[now].a=a;
				seg[now].b=b;
			}
			else
				pushdown(now<<1|1,a,b+(seg[now].len-seg[now<<1|1].len)*a);
		}
		seg[now].update();
		val[now]=std::min(val[now],std::min(val[now<<1],val[now<<1|1]));
		val[now]=std::min(val[now],seg[now].Min);
	}
}
inline ll getMin(int now,int l,int r)
{
	ll li=std::max(l,L[now]);
	ll ri=std::min(r,R[now]);
	if(li>ri)
		return (ll)2e18;
	li=seg[now].b+seg[now].a*(dis[back[li]]-dis[back[L[now]]]);
	ri=seg[now].b+seg[now].a*(dis[back[ri]]-dis[back[L[now]]]);
	return std::min(li,ri);
}
ll query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	ll res=2e18;
	if(l<=mid[now])
		res=std::min(res,query(now<<1,l,r));
	if(r>mid[now])
		res=std::min(res,query(now<<1|1,l,r));
	if(seg[now].has)
		res=std::min(res,getMin(now,l,r));
	return res;
}
ll solve_query(int x,int y)
{
	ll res=2e18;
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			res=std::min(res,query(1,id[top[x]],id[x]));
			x=f[top[x]];
		}
		else
		{
			res=std::min(res,query(1,id[top[y]],id[y]));
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	res=std::min(res,query(1,id[x],id[y]));
	return res;
}
void add(int now,int l,int r,ll a,ll b)
{
	if(L[now]>=l&&R[now]<=r)
	{
		pushdown(now,a,b+a*(dis[back[L[now]]]-dis[back[l]]));
		seg[now].update();
		val[now]=std::min(val[now],seg[now].Min);
		return;
	}
	if(l<=mid[now])
		add(now<<1,l,r,a,b);
	if(r>mid[now])
		add(now<<1|1,l,r,a,b);
	val[now]=std::min(val[now],std::min(val[now<<1],val[now<<1|1]));
	val[now]=std::min(val[now],seg[now].Min);
}
void solve_update(int x,int y,ll a,ll b)
{
	while(top[x]!=top[y])
	{
		add(1,id[top[x]],id[x],-a,b+a*(dis[x]-dis[top[x]]));
		b=b+a*(dis[x]-dis[top[x]]+step[top[x]]);
		x=f[top[x]];
	}
	add(1,id[y],id[x],-a,b+a*(dis[x]-dis[y]));
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	for(int i=1,u,v;i<n;i++)
	{
		ll w;
		read(u);
		read(v);
		read(w);
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=w;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		W[cnt]=w;
		head[v]=cnt;
	}
	cnt=0;
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	int op,s,t,a,b,lca;
	while(m--)
	{
		read(op);
		if(op==1)
		{
			read(s);
			read(t);
			read(a);
			read(b);
			lca=getlca(s,t);
			solve_update(s,lca,a,b);
			solve_update(t,lca,-a,b+(dis[s]+dis[t]-dis[lca]*2)*a);
		}
		else
		{
			read(s);
			read(t);
			printf("%I64d\n",solve_query(s,t));
		}
	}
	return 0;
}
