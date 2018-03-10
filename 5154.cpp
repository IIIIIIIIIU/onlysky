#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+5;
const int INF=0x3f3f3f3f;

int n,s,t,head[maxn],E[maxn],V[maxn],W[maxn],F[maxn];
int	dis[maxn],ans,que[maxn<<1],pre[maxn],hi[105][105];
int cnt,tag[maxn],has[maxn],tot=1;

bool vis[maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
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
	has[cnt]=tot;
	++cnt;
	V[cnt]=u;
}

bool spfa()
{
	for(int i=s;i<=t;i++)
	{
		dis[i]=-INF;
		pre[i]=-1;
		vis[i]=false;
	}
	int h=0,tail=1,now;
	que[h]=s;
	dis[s]=0;
	vis[s]=true;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]&&dis[V[i]]<dis[now]+W[i])
			{
				pre[V[i]]=i;
				dis[V[i]]=dis[now]+W[i];
				if(!vis[V[i]])
				{
					que[tail++]=V[i];
					vis[V[i]]=true;
				}
			}
	}
	return dis[t]!=-INF;
}

int solve()
{
	int res=0;
	while(spfa())
	{
		int now=t;
		while(now!=s)
		{
			if(has[pre[now]^1]!=tot)
			{
				E[pre[now]^1]=head[now];
				head[now]=pre[now]^1;
				W[pre[now]^1]=-W[pre[now]];
				F[pre[now]^1]=0;
				has[pre[now]^1]=tot;
			}
			F[pre[now]]--;
			F[pre[now]^1]++;
			now=V[pre[now]^1];
		}
		res+=dis[t];
	}
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			read(hi[i][v]);
	t=n<<1|1;
	cnt=1;
	for(int i=1;i<=n;i++)
	{
		edge_add(s,i,0,1);
		edge_add(i+n,t,0,1);
		for(int v=1;v<=n;v++)
			edge_add(i,v+n,hi[i][v],1);
	}
	ans=solve();
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		for(int v=head[i+n];v!=0;v=E[v])
			if(V[v]>=1&&V[v]<=n&&F[v]==1)
				tag[i]=V[v];
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
		{
			if(hi[i][v]<hi[tag[v]][v])
				continue;
			++tot;
			for(int e=s;e<=t;e++)
				head[e]=0;
			cnt=1;
			for(int e=1;e<=n;e++)
			{
				edge_add(s,e,0,1);
				edge_add(e+n,t,0,1);
				for(int r=1;r<=n;r++)
					if(e!=i||r!=v)
						edge_add(e,r+n,hi[e][r],1);
			}
			if(solve()!=ans)
				printf("%d %d\n",i,v);
		}
	return 0;
}
