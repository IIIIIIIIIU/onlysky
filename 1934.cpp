#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1005,INF=0x3f3f3f3f;

struct EdgeType
{
	int v,f;

	EdgeType *opposition,*next;

	EdgeType(int v_=0,int f_=0,EdgeType *from=NULL)
	{
		opposition=NULL;
		next=from;
		v=v_,f=f_;
	};
};

struct EdgeType *head[maxn];

int deep[maxn],que[maxn],s,t,n,m;

inline void edge_add(int u,int v,int f1,int f2)
{
	head[u]=new EdgeType(v,f1,head[u]);
	head[v]=new EdgeType(u,f2,head[v]);
	head[u]->opposition=head[v];
	head[v]->opposition=head[u];
}

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

bool bfs()
{
	for(int i=s;i<=t;i++) deep[i]=-1;
	int h=0,tail=1,now;deep[s]=0,que[0]=s;
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

using std::min;

int flowing(int now,int flow)
{
	if(now==t||flow<=0) return flow;
	int oldflow=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->f&&deep[i->v]==deep[now]+1)
		{
			tmp=flowing(i->v,min(flow,i->f));
			i->f-=tmp,i->opposition->f+=tmp,oldflow+=tmp,flow-=tmp;
			if(!flow) return oldflow;
		}
	if(flow) deep[now]=-1;
	return oldflow;
}

int main()
{
	read(n),read(m),t=n+1;
	for(int i=s;i<=t;i++) head[i]=NULL;
	int ux,vx,op;
	for(int i=1;i<=n;i++)
	{
		read(op);
		if(op) edge_add(s,i,1,0);
		else edge_add(i,t,1,0);
	}
	for(int i=1;i<=m;i++)
	{
		read(ux),read(vx);
		edge_add(ux,vx,1,1);
	}
	int ans=0;
	while(bfs()) ans+=flowing(s,INF);
	std::cout<<ans;
	return 0;
}
