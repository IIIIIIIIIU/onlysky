#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const int maxn=1e3+5;
int head[maxn],E[maxn*2],V[maxn*2],cnt,n,m,size;
int ans1,ne,s,tim,ecc,dfn[maxn],low[maxn],cut[maxn];
ll ans2;
inline void edge_add(int u,int v)
{
	E[++ne]=head[u];
	V[ne]=v;
	head[u]=ne;
}
void tarjan(int now,int fa)
{
	dfn[now]=low[now]=++tim;
	int cnt1=0;
	bool f=false;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			if(!dfn[V[i]])
			{
				tarjan(V[i],now);
				cnt1++;
			}
			low[now]=std::min(low[now],low[V[i]]);
			if(dfn[now]<=low[V[i]])
				f=true;
		}
	if((fa==-1&&cnt1>1)||(fa!=-1&&f))
	{
		cut[now]=1;
		cnt++;
	}
}
void dfs(int now,int tim)
{
	dfn[now]=1;
	size++;
	for(int i=head[now];i!=0;i=E[i])
	{
		if(cut[V[i]]&&dfn[V[i]]<tim)
		{
			cnt++;
			dfn[V[i]]=tim;
		}
		if(!dfn[V[i]])
			dfs(V[i],tim);
	}
}
int main()
{
	freopen("data.txt","r",stdin);
	for(int t=1;;t++)
	{
		scanf("%d",&m);
		if(!m)
			return 0;
		n=ne=tim=ans1=cnt=0;
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(cut,0,sizeof(cut));
		for(int i=1,u,v;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			edge_add(u,v);
			edge_add(v,u);
			n=std::max(n,std::max(u,v));
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				tarjan(i,-1);
		ans2=1LL;
		memset(dfn,0,sizeof(dfn));
		if(cnt==0)
		{
			ans1=2;
			ans2=(n*(n-1)/2);
		}
		else
			for(int i=1;i<=n;i++)
			{
				cnt=0;
				if(!cut[i]&&!dfn[i])
				{
					size=0;
					dfs(i,i);
				}
				if(cnt==1)
				{
					ans2*=size;
					ans1++;
				}
			}
		printf("Case %d: %d %llu\n",t,ans1,ans2);
	}
	return 0;
}
