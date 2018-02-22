#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5;
int n,m,head[maxn],E[maxn<<1|1],V[maxn<<1|1],W[maxn<<1|1],cnt;
int deep[maxn],top[maxn],f[maxn],size[maxn],lar[maxn],id[maxn];
int back[maxn];
ll dis[maxn],ans,num;
bool vis[maxn];
std::set<int>Set;
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
			dis[V[i]]=dis[now]+W[i];
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
inline ll getDis(int x,int y)
{
	int lca=getLca(x,y);
	return dis[x]+dis[y]-dis[lca]*2;
}
void add(int x)
{
	int now=id[x];
	Set.insert(now);
	std::set<int>::iterator it=Set.lower_bound(now),pre=Set.end(),suf=Set.end();
	if(it!=Set.begin())
	{
		pre=it;
		--pre;
	}
	suf=it;
	++suf;
	if(pre!=Set.end()&&suf!=Set.end())
		ans-=getDis(back[*pre],back[*suf]);
	if(pre!=Set.end())
		ans+=getDis(x,back[*pre]);
	if(suf!=Set.end())
		ans+=getDis(x,back[*suf]);
}
void del(int x)
{
	int now=id[x];
	std::set<int>::iterator it=Set.lower_bound(now),pre=Set.end(),suf=Set.end();
	if(it!=Set.begin())
	{
		pre=it;
		--pre;
	}
	suf=it;
	++suf;
	if(pre!=Set.end()&&suf!=Set.end())
		ans+=getDis(back[*pre],back[*suf]);
	if(pre!=Set.end())
		ans-=getDis(x,back[*pre]);
	if(suf!=Set.end())
		ans-=getDis(x,back[*suf]);
	Set.erase(it);
}
inline ll getSide()
{
	if(num<=1)
		return 0;
	return getDis(back[*Set.begin()],back[*Set.rbegin()]);
}
int main()
{
	read(n);
	read(m);
	for(int i=1,u,v,w;i<n;i++)
	{
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
	int x;
	while(m--)
	{
		read(x);
		if(vis[x])
		{
			del(x);
			num--;
			vis[x]=false;
		}
		else
		{
			add(x);
			num++;
			vis[x]=true;
		}
		printf("%lld\n",ans+getSide());
	}
	return 0;
}
