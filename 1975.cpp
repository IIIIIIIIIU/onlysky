#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=5005;

const real INF=3e18;

real g[maxn];

struct NodeType
{
	short now;

	real dis;

	NodeType(int now_=0,real dis_=0)
	{
		now=now_,dis=dis_;
	}

	bool operator<(const NodeType &pos)const
	{
		return dis+g[now]>pos.dis+g[pos.now];
	}
};

struct EdgeType
{
	int v;

	real w;

	EdgeType *next;

	EdgeType(int v_=0,real w_=0,EdgeType *next_=NULL)
	{
		v=v_,w=w_,next=next_;
	}
};

struct EdgeType *head[maxn],*opposition_edge[maxn];

int n,m,que[maxn*10];

real sum;

bool vis[maxn];

std::priority_queue<NodeType>Q;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int main()
{
	read(n),read(m),scanf("%lf",&sum);
	for(int i=1;i<=n;i++) head[i]=NULL,opposition_edge[i]=NULL;
	int u,v;real w;
	for(int i=1;i<=m;i++)
	{
		read(u),read(v),scanf("%lf",&w);
		head[u]=new EdgeType(v,w,head[u]);
		opposition_edge[v]=new EdgeType(u,w,opposition_edge[v]);
	}
	int h=0,tail=1,now;
	for(int i=1;i<=n;i++) g[i]=INF;
	g[n]=0,que[0]=n,vis[n]=true;
	while(h<tail)
	{
		now=que[h++],vis[now]=false;
		for(EdgeType *i=opposition_edge[now];i!=NULL;i=i->next)
			if(g[now]+i->w<g[i->v])
			{
				g[i->v]=g[now]+i->w;
				if(!vis[i->v]) vis[i->v]=true,que[tail++]=i->v;
			}
	}
	Q.push(NodeType(1,0));
	NodeType cur;
	int ans=0;
	while(!Q.empty())
	{
		cur=Q.top(),Q.pop();
		if(cur.now==n)
		{
			if(sum>=cur.dis) sum-=cur.dis,ans++;
			else break;
			continue;
		}
		for(EdgeType *i=head[cur.now];i!=NULL;i=i->next)
			Q.push(NodeType(i->v,cur.dis+i->w));
	}
	std::cout<<ans;
	return 0;
}
