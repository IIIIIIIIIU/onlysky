#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=20;
int n,S,bit[maxn],G1size[maxn],G2size[maxn],m;
ll dp[maxn][maxn],ans;
std::vector<int>G1[maxn],G2[maxn];
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
void dfs(int now,int fa)
{
	for(int i=1;i<=n;i++)
		if((bit[i]&S)==0)
			dp[now][i]=1;
	ll tmp;
	for(int i=0;i<G1size[now];i++)
		if(G1[now][i]!=fa)
		{
			dfs(G1[now][i],now);
			tmp=0;
			for(int v=1;v<=n;v++)
			{
				tmp=0;
				for(int e=0;e<G2size[v];e++)
					tmp+=dp[G1[now][i]][G2[v][e]];
				dp[now][v]*=tmp;
			}
		}
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		G2[u].push_back(v);
		G2[v].push_back(u);
	}
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		G1[u].push_back(v);
		G1[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		G1size[i]=G1[i].size();
		G2size[i]=G2[i].size();
	}
	bit[1]=1;
	for(int i=2;i<=n;i++)
		bit[i]=bit[i-1]<<1;
	for(S=0;S<(1<<n);++S)
	{
		memset(dp,0,sizeof(dp));
		dfs(1,0);
		ll sum=0;
		int t=0;
		for(int i=1;i<=n;i++)
			if(!(bit[i]&S))
				sum+=dp[1][i];
			else
				++t;
		if(t%2)
			ans-=sum;
		else
			ans+=sum;
	}
	std::cout<<ans;
	return 0;
}
