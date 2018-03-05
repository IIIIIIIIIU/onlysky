#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=35;
const int mod=1e9+7;
const int maxs=1<<9;

int n,m,k;

ll dp[maxn][maxn][maxs];

inline void add(ll &x,ll y)
{
	if((x+=y)>=mod)
		x-=mod;
}

int main()
{
	std::cin>>n>>m>>k;
	dp[1][0][0]=1;
	/*
	for(int i=2;i<=n;i++)
		for(int v=0;v<=m;v++)
			for(int s=0;s<(1<<(k+1));s++)
			{
				if(!(s&1))
					dp[i][v][s]=dp[i-1][v][s>>1];
				if(v)
					for(int e=1,lit=std::min(k,i-1);e<=lit;++e)
						add(dp[i][v][s],dp[i][v-1][s^(1<<0)^(1<<e)]);
				if(dp[i][v][s])
					printf("%d %d %d %I64d\n",i,v,s,dp[i][v][s]);
			}
			*/
	for(int i=2;i<=n;i++)
	{
		for(int v=0;v<=m;v++)
			for(int s=0;s<(1<<(k+1));s++)
				if(!(s&1))
					dp[i][v][s]=dp[i-1][v][s>>1];
		for(int e=1;e<=k;e++)
			for(int v=0;v<=m;v++)
				for(int s=0;s<(1<<(k+1));s++)
					if(e<=std::min(k,i-1))
						add(dp[i][v][s],dp[i][v-1][s^(1<<0)^(1<<e)]);
	}
	std::cout<<dp[n][m][0]<<std::endl;
	return 0;
}
