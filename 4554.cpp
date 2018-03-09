#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int INF=0x3f3f3f3f;

int n,m,s,t,id1[55][55],id2[55][55],num;
int head[maxn],E[maxn],V[maxn],F[maxn],cnt=1;
int deep[maxn],que[maxn],lit;

bool vis[55][55];

char str[55][55];

inline void edge_add(int u,int v,int f)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=f;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=0;
	head[v]=cnt;
}

inline bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	int h=0,tail=1,now;
	deep[s]=0;
	que[h]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(deep[V[i]]<0&&F[i]>0)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}

int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]>0&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(F[i],flow));
			F[i]-=tmp;
			F[i^1]+=tmp;
			flow-=tmp;
			oldflow+=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}

int main()
{
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
		std::cin>>str[i]+1;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(!vis[i][v]&&str[i][v]=='*')
			{
				++num;
				id1[i][v]=num;
				vis[i][v]=true;
				for(int e=i-1;e>=1&&str[e][v]!='#';e--)
				{
					id1[e][v]=num;
					vis[e][v]=true;
				}
				for(int e=i+1;e<=n&&str[e][v]!='#';e++)
				{
					id1[e][v]=num;
					vis[e][v]=true;
				}
			}
	lit=num;
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(!vis[i][v]&&str[i][v]=='*')
			{
				++num;
				id2[i][v]=num;
				vis[i][v]=true;
				for(int e=v-1;e>=1&&str[i][e]!='#';e--)
				{
					vis[i][e]=true;
					id2[i][e]=num;
				}
				for(int e=v+1;e<=m&&str[i][e]!='#';e++)
				{
					vis[i][e]=true;
					id2[i][e]=num;
				}
			}
	s=0;
	t=num+n*m+1;
	for(int i=1;i<=lit;i++)
		edge_add(s,i,1);
	for(int v=lit+1;v<=num;v++)
		edge_add(v,t,1);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(str[i][v]=='*')
			{
				edge_add(id1[i][v],num+(i-1)*m+v,1);
				edge_add(num+(i-1)*m+v,id2[i][v],1);
			}
	int ans=0;
	while(bfs())
		ans+=flowing(s,INF);
	std::cout<<ans<<std::endl;
	return 0;
}
