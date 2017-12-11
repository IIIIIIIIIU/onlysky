#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=35;
const int INF=0x3f3f3f3f;

struct EdgeType
{
	int u,v,w,f;
	
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

struct EdgeType *head[maxn*maxn*2],*pre[maxn*maxn*2];

int n,m,s,t,id[maxn][maxn],ans,cap[maxn*maxn],cnt,ans1,ans2,ans3,ans4;
int dis[maxn*maxn*2],que[maxn*maxn*maxn*maxn*2];

bool vis[maxn*maxn*2];

char str[maxn];

inline void edge_add(int u,int v,int w,int f)
{
	head[u]=new EdgeType(v,w,f,head[u]);
	head[v]=new EdgeType(u,-w,0,head[v]);
	head[u]->opposition=head[v];
	head[v]->opposition=head[u];
}

bool spfa()
{
	int h=0,tail=1,now;
	for(int i=s;i<=t;i++)
	{
		dis[i]=INF;
		pre[i]=NULL;
		vis[i]=false;
	}
	dis[s]=0;
	que[h]=s;
	vis[s]=true;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			if(i->f>0&&dis[now]+i->w<dis[i->v])
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
	return dis[t]!=INF;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			id[i][v]=++cnt;
	s=0;
	t=cnt<<1|1;
	for(int i=s;i<=t;i++)
		head[i]=NULL;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int v=1;v<=m;v++)
			if(str[v]=='1')
			{
				ans2++;
				cap[id[i][v]]++;
				edge_add(s,id[i][v],-1,1);
			}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int v=1;v<=m;v++)
			if(str[v]=='1')
			{
				ans3++;
				cap[id[i][v]]++;
				edge_add(id[i][v]+cnt,t,-1,1);
			}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int v=1;v<=m;v++)
		{
			cap[id[i][v]]+=str[v]-'0';
			if(cap[id[i][v]])
				edge_add(id[i][v],id[i][v]+cnt,2,cap[id[i][v]]/2);
			if(i>1)
				edge_add(id[i][v]+cnt,id[i-1][v],0,INF);
			if(i<n)
				edge_add(id[i][v]+cnt,id[i+1][v],0,INF);
			if(v>1)
				edge_add(id[i][v]+cnt,id[i][v-1],0,INF);
			if(v<m)
				edge_add(id[i][v]+cnt,id[i][v+1],0,INF);
			if(i>1&&v>1)
				edge_add(id[i][v]+cnt,id[i-1][v-1],0,INF);
			if(i>1&&v<m)
				edge_add(id[i][v]+cnt,id[i-1][v+1],0,INF);
			if(i<n&&v>1)
				edge_add(id[i][v]+cnt,id[i+1][v-1],0,INF);
			if(i<n&&v<m)
				edge_add(id[i][v]+cnt,id[i+1][v+1],0,INF);
		}
	}
	while(spfa())
	{
		ans1++;
		int now=t;
		while(now!=s)
		{
			pre[now]->f--;
			pre[now]->opposition->f++;
			now=pre[now]->opposition->v;
		}
		ans4+=dis[t];
	}
	if(ans2==ans3&&ans2==ans1)
		printf("%d\n",ans4/2);
	else
		printf("-1\n");
	return 0;
}
