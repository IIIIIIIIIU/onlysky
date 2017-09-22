#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=100005;

int n,k,head[maxn],V[maxn<<1],E[maxn<<1],W[maxn<<1],cnt=1;
int dp[maxn][2],lar[maxn][2],len,tag,ans,edge[maxn][2];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

void dfs(int now,int fa)
{
	dp[now][0]=dp[now][1]=lar[now][0]=lar[now][1]=edge[now][1]=edge[now][0]=0;
	for(int i=head[now];i;i=E[i])
		if(V[i]!=fa)
		{
			dfs(V[i],now);
			int tmp=dp[V[i]][1]+W[i];
			if(tmp>dp[now][1])
			{
				dp[now][0]=dp[now][1];
				dp[now][1]=tmp;
				lar[now][0]=lar[now][1];
				lar[now][1]=V[i];
				edge[now][0]=edge[now][1];
				edge[now][1]=i;
			}
			else if(tmp>dp[now][0])
			{
				dp[now][0]=tmp;
				lar[now][0]=V[i];
				edge[now][0]=i;
			}
		}
	if(dp[now][1]+dp[now][0]>len) len=dp[now][1]+dp[now][0],tag=now;
}

int main()
{
	read(n),read(k);
	int u,v;
	for(int i=1;i<n;i++)
	{
		read(u),read(v);
		E[++cnt]=head[u],V[cnt]=v,W[cnt]=1,head[u]=cnt;
		E[++cnt]=head[v],V[cnt]=u,W[cnt]=1,head[v]=cnt;
	}
	dfs(1,0),ans=n*2-len-1;
	if(k==2)
	{
		if(edge[tag][1])
		{
			W[edge[tag][1]]=W[edge[tag][1]^1]=-1;
			int now=V[edge[tag][1]];
			while(edge[now][1])
			{
				W[edge[now][1]]=W[edge[now][1]^1]=-1;
				now=V[edge[now][1]];
			}
		}
		if(edge[tag][0])
		{
			W[edge[tag][0]]=W[edge[tag][0]^1]=-1;
			int now=V[edge[tag][0]];
			while(edge[now][1])
			{
				W[edge[now][1]]=W[edge[now][1]^1]=-1;
				now=V[edge[now][1]];
			}
		}
		len=0;
		dfs(1,0);
		ans=ans-len+1;
	}
	std::cout<<ans;
	return 0;
}
