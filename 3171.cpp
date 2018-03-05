#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int INF=0x3f3f3f3f;

int n,m,head[maxn],E[maxn],V[maxn],size,s,t;
int id[20][20],cnt=1,F[maxn],W[maxn],num,cmp[5]={0,1,1,1,1};
int dis[maxn],que[maxn],pre[maxn];

char str[maxn];

bool vis[maxn];

inline void edge_add(int u,int v,int w,int f)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	W[cnt]=w;
	F[cnt]=f;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	W[cnt]=-w;
	F[cnt]=0;
	head[v]=cnt;
}

bool spfa()
{
	for(int i=s;i<=t;i++)
	{
		pre[i]=-1;
		dis[i]=INF;
		vis[i]=false;
	}
	int h=0,tail=1,now;
	dis[s]=0;
	que[0]=s;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]>0&&dis[V[i]]>dis[now]+W[i])
			{
				pre[V[i]]=i;
				dis[V[i]]=dis[now]+W[i];
				if(!vis[V[i]])
				{
					vis[V[i]]=true;
					que[tail++]=V[i];
				}
			}
	}
	return dis[t]!=INF;
}

int count()
{
	int res=0,now=t;
	while(pre[now]!=-1)
	{
		F[pre[now]]--;
		F[pre[now]^1]++;
		now=V[pre[now]^1];
	}
	return dis[t];
}

int main()
{
	scanf("%d%d",&n,&m);
	char str[20];
	size=n*m;
	t=size*2+1;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			id[i][v]=++num;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int v=1;v<=m;v++)
		{
			edge_add(s,id[i][v],0,1);
			edge_add(id[i][v]+size,t,0,1);
			if(str[v]=='U')
				cmp[1]=0;
			else if(str[v]=='L')
				cmp[2]=0;
			else if(str[v]=='R')
				cmp[3]=0;
			else
				cmp[4]=0;
			edge_add(id[i][v],id[(i-1)?(i-1):n][v]+size,cmp[1],1);
			edge_add(id[i][v],id[i][(v-1)?(v-1):m]+size,cmp[2],1);
			edge_add(id[i][v],id[i][(v==m)?1:(v+1)]+size,cmp[3],1);
			edge_add(id[i][v],id[(i==n)?1:(i+1)][v]+size,cmp[4],1);
			if(str[v]=='U')
				cmp[1]=1;
			else if(str[v]=='L')
				cmp[2]=1;
			else if(str[v]=='R')
				cmp[3]=1;
			else
				cmp[4]=1;
		}
	}
	int ans=0;
	while(spfa())
		ans+=count();
	std::cout<<ans<<std::endl;
	return 0;
}
