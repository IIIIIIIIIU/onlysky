#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e2+5;
const int maxm=1e6+5;
const int INF=0x3f3f3f3f;

int n,m,head[maxm],E[maxm],V[maxm],W[maxm],F[maxm];
int cnt=1,tot,map[maxn][maxn],id[maxn][maxn],s,t;
int dis[maxm],pre[maxm],que[maxm],X[maxm],Y[maxm];

bool vis[maxm];

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
	que[h]=s;
	vis[s]=true;
	dis[s]=0;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]&&dis[V[i]]>dis[now]+W[i])
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
	return dis[t]<INF;
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			read(map[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=0;v<=n-2;v++)
			edge_add(s,i,v,1);
	tot=n;
	for(int i=1;i<=n;i++)
		for(int v=i+1;v<=n;v++)
		{
			id[i][v]=++tot;
			id[v][i]=tot;
			X[tot]=i;
			Y[tot]=v;
		}
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			if(map[i][v])
				edge_add(i,id[i][v],0,1);
	t=tot+1;
	for(int i=n+1;i<=tot;i++)
		edge_add(i,t,0,1);
	int ans=n*(n-1)*(n-2)/6;
	while(spfa())
	{
		int now=t,pos=INF;
		while(pre[now]!=-1)
		{
			if(pos>F[pre[now]])
				pos=F[pre[now]];
			now=V[pre[now]^1];
		}
		now=t;
		while(pre[now]!=-1)
		{
			F[pre[now]]-=pos;
			F[pre[now]^1]+=pos;
			now=V[pre[now]^1];
		}
		ans-=dis[t]*pos;
	}
	printf("%d\n",ans);
	for(int now=1;now<=n;now++)
		for(int i=head[now];i!=0;i=E[i])
			if(!F[i]&&V[i]>n&&V[i]<t)
				if(now==X[V[i]])
					map[now][Y[V[i]]]=1;
				else
					map[now][X[V[i]]]=1;
	for(int i=1;i<=n;i++)
	{
		for(int v=1;v<=n;v++)
			if(map[i][v]==1)
				printf("1 ");
			else
				printf("0 ");
		printf("\n");
	}
	return 0;
}
