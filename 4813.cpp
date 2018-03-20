#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e2+5;

int n,m,head[maxn],E[maxn],V[maxn],deep[maxn],ans,cnt;

void dfs(int now,int fa)
{
	deep[now]=deep[fa]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
}

inline int get(int x)
{
	if(deep[x]-1>m)
		return 0;
	int t=m-deep[x]+1;
	return deep[x]+std::min(t>>1,n-deep[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		++u;
		++v;
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		ans=std::max(ans,get(i));
	std::cout<<ans<<std::endl;
	return 0;
}
