#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e3+5+200;
const int maxm=6e3+5;
const int INF=0x3f3f3f3f;
int n,m,p,head[maxn],E[maxm],V[maxm],W[maxm],cnt,bel[maxn];
int dp[maxn][maxn],que[maxn*maxn*3],bit[11],ci[maxn],di[maxn];
int val[11],f[maxn],vis[maxn];
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
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(p);
	memset(dp,0x3f,sizeof(dp));
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=w;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		W[cnt]=w;
		head[v]=cnt;
	}
	bit[1]=1;
	for(int i=2;i<=p;i++)
		bit[i]=bit[i-1]<<1;
	for(int i=1;i<=p;i++)
	{
		read(ci[i]);
		read(di[i]);
		bel[ci[i]]|=bit[i];
		dp[bit[i]][di[i]]=0;
	}
	for(int s=0;s<(1<<p);s++)
	{
		int h=0,tail=0,now;
		f[s]=INF;
		int ba=0,t=s;
		for(int v=1;v<=p;v++)
			if((t&bel[v])==bel[v])
				t-=bel[v];
		if(!t)
			ba=true;
		for(int v=1;v<=n;v++)
		{
			vis[v]=false;
			for(int x=s;x;x=(s&(x-1)))
				dp[s][v]=std::min(dp[s][v],dp[x][v]+dp[s^x][v]);
			if(dp[s][v]!=INF)
			{
				vis[v]=true;
				que[tail++]=v;
				if(ba)
					f[s]=std::min(f[s],dp[s][v]);
			}
		}
		while(h<tail)
		{
			now=que[h++];
			vis[now]=false;
			for(int i=head[now];i!=0;i=E[i])
				if(dp[s][now]+W[i]<dp[s][V[i]])
				{
					dp[s][V[i]]=dp[s][now]+W[i];
					if(!vis[V[i]])
					{
						vis[V[i]]=true;
						que[tail++]=V[i];
					}
				}
		}
	}
	for(int s=0;s<(1<<p);s++)
		for(int x=s;x;x=(s&(x-1)))
			f[s]=std::min(f[s],f[s^x]+f[x]);
	std::cout<<f[(1<<p)-1]<<std::endl;
	return 0;
}
