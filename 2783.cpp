#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
int ai[maxn],bi[maxn],head[maxn],E[maxn<<1];
int V[maxn<<1],cnt,s,count[maxn],ans,n;
std::map<int,int>Map;
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
void dfs(int now,int fa)
{
	ai[now]+=ai[fa];
	bi[now]=ai[now];
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
}
void dfs2(int now,int fa)
{
	ans+=count[Map[ai[now]-s]];
	count[Map[ai[now]]]++;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs2(V[i],now);
	count[Map[ai[now]]]--;
}
int main()
{
	read(n);
	read(s);
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
	dfs(1,0);
	bi[n+1]=0;
	std::sort(bi+1,bi+n+2);
	int size=std::unique(bi+1,bi+n+2)-bi-1;
	for(int i=1;i<=size;i++)
		Map[bi[i]]=i;
	count[1]++;
	dfs2(1,0);
	std::cout<<ans;
	return 0;
}
