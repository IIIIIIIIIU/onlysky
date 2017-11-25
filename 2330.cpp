#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;

struct Edge
{
	int u,v,w;
	
	void make(int u_,int v_,int w_)
	{
		u=u_;
		v=v_;
		w=w_;
	}
};

struct Edge edge[maxn<<2];

struct EdgeType
{
	int v,w;
	
	EdgeType *next;
	
	EdgeType(){}
	
	EdgeType(int v_,int w_,EdgeType *next_)
	{
		v=v_;
		w=w_;
		next=next_;
	}
};

struct EdgeType *head[maxn],*head2[maxn];

int n,m,dfn[maxn],low[maxn],Stack[maxn],top,col,bel[maxn];
int tag,size[maxn],cnt,dis[maxn],du[maxn],que[maxn],ans;

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

void tarjan(int now)
{
	dfn[now]=low[now]=++tag;
	Stack[++top]=now;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(!bel[i->v])
			if(dfn[i->v])
				low[now]=std::min(low[now],dfn[i->v]);
			else
			{
				tarjan(i->v);
				low[now]=std::min(low[now],low[i->v]);
			}
	if(low[now]==dfn[now])
	{
		col++;
		size[col]=1;
		while(Stack[top]!=now)
		{
			bel[Stack[top--]]=col;
			size[col]++;
		}
		bel[now]=col;
		top--;
	}
}

int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	for(int i=1,x,a,b;i<=m;i++)
	{
		read(x);
		read(a);
		read(b);
		if(x==1)
		{
			head[a]=new EdgeType(b,0,head[a]);
			head[b]=new EdgeType(a,0,head[b]);
			edge[++cnt].make(a,b,0);
			edge[++cnt].make(b,a,0);
		}
		else if(x==2)
		{
			head[a]=new EdgeType(b,1,head[a]);
			edge[++cnt].make(a,b,1);
		}
		else if(x==3)
		{
			head[b]=new EdgeType(a,0,head[b]);
			edge[++cnt].make(b,a,0);
		}
		else if(x==4)
		{
			head[b]=new EdgeType(a,1,head[b]);
			edge[++cnt].make(b,a,1);
		}
		else
		{
			head[a]=new EdgeType(b,0,head[a]);
			edge[++cnt].make(a,b,0);
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=cnt;i++)
		if(bel[edge[i].u]==bel[edge[i].v]&&edge[i].w)
		{
			puts("-1");
			return 0;
		}
	for(int i=1;i<=col;i++)
		head2[i]=NULL;
	for(int i=1;i<=cnt;i++)
	{
		if(bel[edge[i].u]!=bel[edge[i].v])
		{
			head2[bel[edge[i].u]]=new EdgeType(bel[edge[i].v],edge[i].w,head2[bel[edge[i].u]]);
			du[bel[edge[i].v]]++;
		}
	}
	int h=0,tail=0,now;
	for(int i=1;i<=col;i++)
		if(!du[i])
			que[tail++]=i;
	ll ans=0;
	while(h<tail)
	{
		now=que[h++];
		if(!dis[now])
			dis[now]=1;
		ans+=dis[now]*size[now];
		for(EdgeType *i=head2[now];i!=NULL;i=i->next)
		{
			dis[i->v]=std::max(dis[i->v],dis[now]+i->w);
			if(!(--du[i->v]))
				que[tail++]=i->v;
		}
	}
	std::cout<<ans;
	return 0;
}
