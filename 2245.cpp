#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1005;
const int INF=0x3f3f3f3f;

struct EdgeType
{
	int v,w,f;
	
	EdgeType *next,*opposition;
	
	EdgeType(){}
	
	EdgeType(int v_,int w_,int f_,EdgeType *next_)
	{
		v=v_;
		w=w_;
		f=f_;
		next=next_;
	}
};

struct EdgeType *head[maxn],*pre[maxn];

int n,m,s,t,ai[maxn],que[maxn*maxn*5],dis[maxn];

bool vis[maxn];

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

inline void edge_add(int u,int v,int w,int f)
{
	head[u]=new EdgeType(v,w,f,head[u]);
	head[v]=new EdgeType(u,-w,0,head[v]);
	head[u]->opposition=head[v];
	head[v]->opposition=head[u];
}

bool spfa()
{
	for(int i=s;i<=t;i++)
	{
		dis[i]=INF;
		pre[i]=NULL;
		vis[i]=false;
	}
	dis[s]=0;
	int h=0,tail=1,now;
	que[0]=s;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			if(i->f&&dis[i->v]>dis[now]+i->w)
			{
				pre[i->v]=i;
				dis[i->v]=dis[now]+i->w;
				if(!vis[i->v])
				{
					vis[i->v]=true;
					que[tail++]=i->v;
				}
			}
	}
	return dis[t]<INF;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(m);
	read(n);
	s=0;
	t=n+m+1;
	for(int i=s;i<=t;i++)
		head[i]=NULL;
	for(int i=1,tmp;i<=n;i++)
	{
		read(tmp);
		edge_add(s,i,0,tmp);
	}
	for(int i=1,tmp;i<=m;i++)
		for(int v=1;v<=n;v++)
		{
			read(tmp);
			if(tmp)
				edge_add(v,i+n,0,INF);
		}
	for(int i=1,S,tmp,last;i<=m;i++)
	{
		read(S);
		for(int v=1;v<=S;v++)
			read(ai[v]);
		ai[++S]=INF;
		for(int v=1;v<=S;v++)
		{
			read(tmp);
			edge_add(i+n,t,tmp,ai[v]-ai[v-1]);
		}
	}
	ll ans=0;
	while(spfa())
	{
		int now=t,flow=INF;
		while(pre[now]!=NULL)
		{
			if(pre[now]->f<flow)
				flow=pre[now]->f;
			now=pre[now]->opposition->v;
		}
		now=t;
		while(pre[now]!=NULL)
		{
			pre[now]->f-=flow;
			pre[now]->opposition->f+=flow;
			now=pre[now]->opposition->v;
		}
		ans+=flow*dis[t];
	}
	std::cout<<ans;
	return 0;
}
