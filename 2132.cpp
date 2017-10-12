#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=105,INF=0x3f3f3f3f;

struct EdgeType
{
	int v,f;

	EdgeType *next,*opposition;

	EdgeType(int v_=0,int f_=0,EdgeType *next_=NULL)
	{
		v=v_,f=f_,next=next_;
	}
};

struct EdgeType *head[maxn*maxn];

int n,m,id[maxn][maxn],ai[maxn][maxn],bi[maxn][maxn],ci[maxn][maxn];
int cnt,s,t,ans,deep[maxn*maxn],que[maxn*maxn];

bool type[maxn][maxn];

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

int flowing(int now,int flow)
{
	if(now==t||flow<=0) return flow;
	int oldflow=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->f&&deep[i->v]==deep[now]+1)
		{
			tmp=flowing(i->v,std::min(i->f,flow));
			i->f-=tmp,i->opposition->f+=tmp,oldflow+=tmp,flow-=tmp;
			if(!flow) return oldflow;
		}
	if(flow) deep[now]=-1;
	return oldflow;
}

int main()
{
//	freopen("nt2011_land.in","r",stdin);
//	freopen("nt2011_land.out","w",stdout);
	read(n),read(m);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			id[i][v]=++cnt,type[i][v]=(i+v)%2;
	t=++cnt;
	for(int i=s;i<=t;i++) head[i]=NULL;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(ai[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(bi[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(ci[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(type[i][v])
				std::swap(ai[i][v],bi[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			edge_add(s,id[i][v],ai[i][v],0);
			edge_add(id[i][v],t,bi[i][v],0);
			ans+=ai[i][v]+bi[i][v];
			if(type[i][v])
			{
				if(i-1>0) edge_add(id[i][v],id[i-1][v],ci[i][v]+ci[i-1][v],ci[i][v]+ci[i-1][v]),ans+=ci[i][v]+ci[i-1][v];
				if(i+1<=n) edge_add(id[i][v],id[i+1][v],ci[i][v]+ci[i+1][v],ci[i][v]+ci[i+1][v]),ans+=ci[i][v]+ci[i+1][v];
				if(v-1>0) edge_add(id[i][v],id[i][v-1],ci[i][v]+ci[i][v-1],ci[i][v]+ci[i][v-1]),ans+=ci[i][v]+ci[i][v-1];
				if(v+1<=m) edge_add(id[i][v],id[i][v+1],ci[i][v]+ci[i][v+1],ci[i][v]+ci[i][v+1]),ans+=ci[i][v]+ci[i][v+1];
			}
		}
	while(bfs()) ans-=flowing(s,INF);
	std::cout<<ans;
	return 0;
}
