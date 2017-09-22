#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=205;

struct node
{
	int p,s;
	bool operator<(const node &pos)const
	{
		return s>pos.s;
	}
};
struct node ai[maxn];

int n,sum[maxn],dp[205][40005];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++) read(ai[i].p),read(ai[i].s);
	std::sort(ai+1,ai+n+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+ai[i].p;
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int v=0;v<=sum[i];v++)
		{
			if(v>=ai[i].p) 
//			{
				dp[i][v]=std::min(dp[i][v],std::max(dp[i-1][v-ai[i].p],v+ai[i].s));
//				printf("%d %d %d\n",i,v,dp[i][v]);
//			}
			if(v<=sum[i]-ai[i].p)
//			{
				dp[i][v]=std::min(dp[i][v],std::max(dp[i-1][v],sum[i]-v+ai[i].s));
//				printf("%d %d %d\n",i,v,dp[i][v]);
//			}
		}
	int ans=0x7fffffff;
	for(int i=0;i<=sum[n];i++) ans=std::min(ans,dp[n][i]);
	std::cout<<ans;
	return 0;
}
