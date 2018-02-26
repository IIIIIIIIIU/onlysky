#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e5+5;
typedef long long ll;
int n,m,fa[maxn],a[maxn],c[maxn],fir[maxn],nxt[maxn<<1];
int to[maxn<<1],tot=1,dep[maxn],ans[maxn],num[maxn];
ll h[maxn],v[maxn],s[maxn];
std::vector<int>p[maxn];
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
struct heap
{
	heap *ch[2],*fa;
	int dep,h,id;
	ll tag,tag_,x;
	inline void times(ll d)
	{
		x*=d;
		tag*=d;
		tag_*=d;
	}
	inline void add(ll d)
	{
		x+=d;
		tag_+=d;
	}
	inline void pushdown()
	{
		if(ch[0])
		{
			ch[0]->times(tag);
			ch[0]->add(tag_);
		}
		if(ch[1])
		{
			ch[1]->times(tag);
			ch[1]->add(tag_);
		}
		tag=1;
		tag_=0;
	}
	friend heap *merge(heap *a,heap *b)
	{
		#define height(p) ((p)?p->h:0)
		if(!a)
			return b;
		if(!b)
			return a;
		if(a->x>b->x)
			std::swap(a,b);
		a->pushdown();
		a->ch[1]=merge(a->ch[1],b);
		if(height(a->ch[1])>height(a->ch[0]))
			std::swap(a->ch[0],a->ch[1]);
		a->h=height(a->ch[1])+1;
		return a;
	}
	heap *pop()
	{
		this->pushdown();
		return merge(ch[0],ch[1]);
	}
};
struct heap pool[maxn],*tail=pool;
heap *newnode(ll x,ll d)
{
	tail->x=s[x];
	tail->id=x;
	tail->dep=d;
	tail->h=tail->tag=1;
	tail->tag_=0;
	tail->ch[0]=tail->ch[1]=0;
	return tail++;
}
inline void add(int u,int v)
{
	to[++tot]=v;
	nxt[tot]=fir[u];
	fir[u]=tot;
}
heap *dfs(int x)
{
	dep[x]=dep[fa[x]]+1;
	heap *cur=0;
	for(int i=0;i<p[x].size();i++)
		cur=merge(cur,newnode(p[x][i],dep[x]));
	for(int i=fir[x];i;i=nxt[i])
		if(to[i]!=fa[x])
			cur=merge(cur,dfs(to[i]));
	for(;cur&&cur->x<h[x];cur=cur->pop())
	{
		cur->pushdown();
		num[cur->id]=cur->dep-dep[x];
		ans[x]++;
	}
	if(cur)
		(a[x]?cur->times(v[x]):cur->add(v[x]));
	return cur;
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		read(h[i]);
	for(int i=2;i<=n;i++)
	{
		read(fa[i]);
		read(a[i]);
		read(v[i]);
		add(i,fa[i]);
		add(fa[i],i);
	}
	for(int i=1;i<=m;i++)
	{
		read(s[i]);
		read(c[i]);
		p[c[i]].push_back(i);
	}
	heap *cur=dfs(1);
	for(;cur;cur=cur->pop())
	{
		cur->pushdown();
		num[cur->id]=cur->dep;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	for(int i=1;i<=m;i++)
		printf("%d\n",num[i]);
	return 0;
}
