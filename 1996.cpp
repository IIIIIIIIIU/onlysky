#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int mod=19650827,maxn=1005;

int n,ai[maxn],dp[maxn][maxn][2];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++) read(ai[i]),dp[i][i][0]=1;
	for(int k=1;k<=n-1;k++)
		for(int i=1;i+k<=n;i++)
		{
			int j=i+k;
			if(ai[i]<ai[i+1]) dp[i][j][0]=dp[i+1][j][0];
			if(ai[i]<ai[j]) (dp[i][j][0]+=dp[i+1][j][1])%=mod;
			if(ai[j]>ai[j-1]) dp[i][j][1]=dp[i][j-1][1];
			if(ai[j]>ai[i]) (dp[i][j][1]+=dp[i][j-1][0])%=mod;
		}
	std::cout<<(dp[1][n][0]+dp[1][n][1])%mod;
	return 0;
}
