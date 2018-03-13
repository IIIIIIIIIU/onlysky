#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;

int n,head[maxn],E[maxn],V[maxn],cnt,top[maxn];
int size[maxn],lar[maxn],m,order[maxn],deep[maxn];
int ai[maxn],blockSize,bel[maxn],li[maxn],ri[maxn];
int num[maxn],count[maxn],f[maxn],To[maxn],Xi[maxn];
int block,ans[maxn],back[maxn];

bool vis[maxn];

struct QueryType
{
	int id,times,u,v;
	
	inline bool operator<(const QueryType &tmp)const
	{
		if(bel[order[u]]==bel[order[tmp.u]])
			return order[v]<order[tmp.v];
		return bel[order[u]]<bel[order[u]];
	}
};

struct QueryType qu[maxn];

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

inline void update(int x,bool d)
{
	if(x<=n)
	{
		if(d)
		{
			if(++num[x]==1)
				count[bel[x]]++;
		}
		else
		{
			if(--num[x]==0)
				count[bel[x]]--;
		}
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
			if(size[V[i]]>size[lar[now]])
				lar[now]=V[i];
		}
}

void dfs2(int now,int chain)
{
	top[now]=chain;
	order[now]=++cnt;
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
	return deep[x]>deep[y]?y:x;
}

inline int getAns()
{
	for(int i=1;i<=block;i++)
		if(count[i]<ri[i]-li[i]+1)
		{
			for(int v=li[i];v<=ri[i];v++)
				if(!num[v])
					return v;
		}
}

inline void updateT(int t,bool d)
{
	if(d)
	{
		back[t]=ai[To[t]];
		if(vis[To[t]])
			update(ai[To[t]],false);
		ai[To[t]]=Xi[t];
		if(vis[To[t]])
			update(Xi[t],true);
	}
	else
	{
		if(vis[To[t]])
			update(ai[To[t]],false);
		ai[To[t]]=back[t];
		if(vis[To[t]])
			update(ai[To[t]],true);
	}
}

inline void solve(int now,int to)
{
	while(now!=to)
	{
		update(ai[now],vis[now]=!vis[now]);
		now=f[now];
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	blockSize=std::sqrt(n);
	for(int i=0;i<=n;i++)
	{
		bel[i]=i/blockSize+1;
		if(!li[bel[i]])
			li[bel[i]]=i;
		ri[bel[i]]=i;
		block=bel[i];
	}
	li[1]=0;
	for(int i=1;i<=n;i++)
		read(ai[i]);
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
	int changeT=0,queryT=0;
	for(int i=1,op;i<=m;i++)
	{
		read(op);
		if(op)
		{
			queryT++;
			read(qu[queryT].u);
			read(qu[queryT].v);
			if(order[qu[queryT].u]>order[qu[queryT].v])
				std::swap(qu[queryT].u,qu[queryT].v);
			qu[queryT].id=queryT;
			qu[queryT].times=changeT;
		}
		else
		{
			changeT++;
			read(To[changeT]);
			read(Xi[changeT]);
		}
	}
	std::sort(qu+1,qu+queryT+1);
	int nowU=1,nowV=1,nowT=0,tU,tV,tT,lca;
	for(int i=1;i<=queryT;i++)
	{
		tU=qu[i].u;
		tV=qu[i].v;
		tT=qu[i].times;
		while(nowT<tT)
			updateT(++nowT,true);
		while(nowT>tT)
			updateT(nowT--,false);
		lca=getLca(tU,nowU);
		solve(nowU,lca);
		solve(tU,lca);
		lca=getLca(tV,nowV);
		solve(nowV,lca);
		solve(tV,lca);
		lca=getLca(tU,tV);
		update(ai[lca],!vis[lca]);
		ans[qu[i].id]=getAns();
		update(ai[lca],vis[lca]);
		nowU=tU;
		nowV=tV;
	}
	for(int i=1;i<=queryT;i++)
		printf("%d\n",ans[i]);
	return 0;
}
