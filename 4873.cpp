#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+5;
const int INF=0x3f3f3f3f;

int n,m,head[maxn],E[maxn<<1|1],V[maxn<<1|1];
int num,dis[105][105],id[105][105],ai[maxn];
int s,t,deep[maxn],que[maxn],cnt=1,F[maxn<<1|1];

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
	deep[s]=0;
	int h=0,tail=1,now;
	que[h]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]>0&&deep[V[i]]<0)
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
	int ans=0;
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
		std::cin>>ai[i];
	for(int i=1;i<=n;i++)
		for(int v=i;v<=n;v++)
		{
			std::cin>>dis[i][v];
			id[i][v]=++num;
		}
	s=0;
	t=num+1001+1;
	for(int i=0;i<=1000;i++)
		edge_add(num+i+1,t,m*i*i);
	for(int i=1;i<=n;i++)
	{
		edge_add(id[i][i],num+1+ai[i],INF);
		if(dis[i][i]-ai[i]>=0)
		{
			ans+=dis[i][i]-ai[i];
			edge_add(s,id[i][i],dis[i][i]-ai[i]);
		}
		else
			edge_add(id[i][i],t,ai[i]-dis[i][i]);
	}
	for(int len=2;len<=n;len++)
		for(int l=1,r;(r=l+len-1)<=n;l++)
		{
			if(dis[l][r]>=0)
			{
				ans+=dis[l][r];
				edge_add(s,id[l][r],dis[l][r]);
			}
			else
				edge_add(id[l][r],t,-dis[l][r]);
			edge_add(id[l][r],id[l+1][r],INF);
			edge_add(id[l][r],id[l][r-1],INF);
		}
	while(bfs())
		ans-=flowing(s,INF);
	std::cout<<ans<<std::endl;
	return 0;
}
