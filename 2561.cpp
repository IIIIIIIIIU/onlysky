#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e4+5;
const int maxm=4e5+5;
const int INF=0x3f3f3f3f;

struct EdgeType
{
	int u,v,w;
};

struct EdgeType edge[maxm];

int n,m,head[maxn],E[maxm],V[maxm],F[maxm],cnt,Ans;
int que[maxn],deep[maxn],s,t,lit;

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

inline void edge_add(int u,int v)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=1;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=1;
	head[v]=cnt;
}

bool bfs()
{
	for(int i=1;i<=n;i++)
		deep[i]=-1;
	deep[s]=0;
	int h=0,tail=1,now;
	que[h]=s;
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
		if(F[i]&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
			flow-=tmp;
			oldflow+=tmp;
			F[i]-=tmp;
			F[i^1]+=tmp;
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
	for(int i=1;i<=m;i++)
	{
		read(edge[i].u);
		read(edge[i].v);
		read(edge[i].w);
	}
	read(s);
	read(t);
	read(lit);
	cnt=1;
	for(int i=1;i<=m;i++)
		if(edge[i].w<lit)
			edge_add(edge[i].u,edge[i].v);
	while(bfs())
		Ans+=flowing(s,INF);
	for(int i=1;i<=n;i++)
		head[i]=0;
	cnt=1;
	for(int i=1;i<=m;i++)
		if(edge[i].w>lit)
			edge_add(edge[i].u,edge[i].v);
	while(bfs())
		Ans+=flowing(s,INF);
	std::cout<<Ans;
	return 0;
}
