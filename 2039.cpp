#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1005,INF=1e9;

struct EdgeType
{
	int v,f;

	EdgeType *next,*opposition;

	EdgeType(int v_=0,int f_=0,EdgeType *next_=NULL)
	{
		v=v_,f=f_,next=next_,opposition=NULL;
	}
};

struct EdgeType *head[maxn];

int n,ai[maxn],e[maxn][maxn],sum[maxn],s,t,all,deep[maxn];
int que[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline void edge_add(int u,int v,int f1,int f2)
{
	head[u]=new EdgeType(v,f1,head[u]);
	head[v]=new EdgeType(u,f2,head[v]);
	head[u]->opposition=head[v];
	head[v]->opposition=head[u];
}

bool bfs()
{
	for(int i=s;i<=t;i++) deep[i]=-1;
	int h=0,tail=1,now;que[0]=s,deep[s]=0;
	while(h<tail)
		for(EdgeType *i=head[now=que[h++]];i!=NULL;i=i->next)
			if(i->f&&deep[i->v]<0)
			{
				deep[i->v]=deep[now]+1;
				if(i->v==t) return true;
				que[tail++]=i->v;
			}
	return false;
}

int flowing(int now,int flow)
{
	if(now==t||flow<=0) return flow;
	int oldflow=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->f&&deep[i->v]==deep[now]+1)
		{
			tmp=flowing(i->v,std::min(i->f,flow));
			flow-=tmp,oldflow+=tmp,i->f-=tmp,i->opposition->f+=tmp;
			if(!flow) return oldflow;
		}
	if(flow) deep[now]=-1;
	return oldflow;
}

int main()
{
	read(n);
	s=0,t=n+1;
	for(int i=s;i<=t;i++)
		head[i]=NULL;
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		edge_add(i,t,ai[i],0);
	}
	for(int i=1;i<=n;i++)
	{
		for(int v=1;v<=n;v++)
		{
			read(e[i][v]);
			sum[i]+=e[i][v];
			all+=e[i][v];
			if(v>i) edge_add(i,v,e[i][v]<<1,e[i][v]<<1);
		}
		edge_add(s,i,sum[i],0);
	}
	while(bfs())
		all-=flowing(s,INF);
	std::cout<<all;
	return 0;
}
