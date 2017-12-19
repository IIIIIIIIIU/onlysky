#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e2+5;
const int INF=0x3f3f3f3f;
int n,m,head[maxn],s,t,E[maxn*maxn*2],V[maxn*maxn*2],F[maxn*maxn*2],cnt=1;
int que[maxn],deep[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
inline void edge_add(int u,int v,int f1,int f2)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=f1;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=f2;
	head[v]=cnt;
}
bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	int h=0,tail=1,now;
	que[0]=s;
	while(h<tail)
		for(int i=head[now=que[h++]];i!=0;i=E[i])
			if(deep[V[i]]<0&&F[i])
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	return false;
}
int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(deep[V[i]]==deep[now]+1&&F[i])
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
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
	read(n);
	read(m);
	s=0;
	t=n+1;
	for(int i=1,x;i<=n;i++)
	{
		read(x);
		if(x)
			edge_add(i,t,1,0);
		else
			edge_add(s,i,1,0);
	}
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		edge_add(u,v,1,1);
	}
	int ans=0;
	while(bfs())
		ans+=flowing(s,INF);
	std::cout<<ans;
	return 0;
}
