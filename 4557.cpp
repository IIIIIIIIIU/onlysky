#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=5e5+5;
const int INF=0x3f3f3f3f;

int n,m,g[maxn][22],f[maxn][22],wi[maxn],cnt;
int head[maxn],E[maxn<<1|1],V[maxn<<1|1],num;

bool vis[maxn];

void dfs(int now,int fa)
{
	if(vis[now])
		g[now][0]=f[now][0]=wi[now];
	for(int i=1;i<=m;i++)
		f[now][i]=wi[now];
	f[now][m+1]=INF;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dfs(V[i],now);
			for(int v=m;v>=0;v--)
				f[now][v]=std::min(f[now][v]+g[V[i]][v],g[now][v+1]+f[V[i]][v+1]);
			for(int v=m;v>=0;v--)
				f[now][v]=std::min(f[now][v],f[now][v+1]);
			g[now][0]=f[now][0];
			for(int v=1;v<=m;v++)
				g[now][v]+=g[V[i]][v-1];
			for(int v=1;v<=m;v++)
				g[now][v]=std::min(g[now][v],g[now][v-1]);
		}
}

int main()
{
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
		std::cin>>wi[i];
	std::cin>>num;
	for(int i=1,x;i<=num;i++)
	{
		std::cin>>x;
		vis[x]=true;
	}
	for(int i=1,u,v;i<n;i++)
	{
		std::cin>>u>>v;
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	dfs(1,0);
	std::cout<<f[1][0]<<std::endl;
	return 0;
}
