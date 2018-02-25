#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=5e6+5;
const int INF=0x3f3f3f3f;
int n,m,head[maxn],E[maxn],V[maxn],F[maxn],ans,cnt=1;
int deep[maxn],que[maxn],s,t;
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
inline bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	deep[s]=0;
	int h=0,tail=1,now;
	que[0]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(deep[V[i]]<0&&F[i])
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}
inline int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(deep[now]+1==deep[V[i]]&&F[i])
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
int main()
{
	read(n);
	s=0;
	t=n*n+n+1;
	for(int i=1,tmp=0,x;i<=n;i++)
		for(int v=1;v<=n;v++)
		{
			++tmp;
			read(x);
			edge_add(s,tmp,x);
			edge_add(tmp,i+n*n,INF);
			edge_add(tmp,v+n*n,INF);
			ans+=x;
		}
	for(int i=1,x;i<=n;i++)
	{
		read(x);
		edge_add(i+n*n,t,x);
	}
	while(bfs())
		ans-=flowing(s,INF);
	std::cout<<ans<<std::endl;
	return 0;
}
