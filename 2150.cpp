#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=55*55*2+1,INF=0x3f3f3f3f;

struct EdgeType
{
	int v,f;

	EdgeType *next,*opposition;

	EdgeType(int v_,int f_,EdgeType *next_)
	{
		v=v_,f=f_,next=next_;
	}
};

struct EdgeType *head[maxn];

int n,m,R,C,id[55][55],cnt,ans,deep[maxn],que[maxn],s,t;

char map[55][55];

inline void edge_add(int u,int v,int f)
{
	head[u]=new EdgeType(v,f,head[u]);
	head[v]=new EdgeType(u,0,head[v]);
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
			tmp=flowing(i->v,std::min(flow,i->f));
			flow-=tmp,oldflow+=tmp,i->f-=tmp,i->opposition->f+=tmp;
			if(!flow) return oldflow;
		}
	if(!oldflow) deep[now]=-1;
	return oldflow;
}

int main()
{
//	freopen("lanzerb.in","r",stdin);
//	freopen("lanzerb.out","w",stdout);
	std::cin>>n>>m>>R>>C;
	for(int i=1;i<=n;i++)
	{
		std::cin>>map[i]+1;
		for(int v=1;v<=m;v++)
			id[i][v]=++cnt;
	}
	t=cnt<<1|1;
	for(int i=s;i<=t;i++) head[i]=NULL;
	for(int i=1;i<=n;i++)
	{
		for(int v=1;v<=m;v++)
			if(map[i][v]=='.')
			{
				edge_add(s,id[i][v],1);
				edge_add(id[i][v]+cnt,t,1);
				++ans;
				if(i+R<=n&&v+C<=m&&map[i+R][v+C]=='.')
					edge_add(id[i][v],id[i+R][v+C]+cnt,1);
				if(i+R<=n&&v-C>0&&map[i+R][v-C]=='.')
					edge_add(id[i][v],id[i+R][v-C]+cnt,1);
				if(R!=C&&i+C<=n&&v+R<=m&&map[i+C][v+R]=='.')
					edge_add(id[i][v],id[i+C][v+R]+cnt,1);
				if(R!=C&&i+C<=n&&v-R>0&&map[i+C][v-R]=='.')
					edge_add(id[i][v],id[i+C][v-R]+cnt,1);
			}
	}
	while(bfs()) ans-=flowing(s,INF);
	std::cout<<ans;
	return 0;
}
