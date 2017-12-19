#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e3+5;
const int INF=0x3f3f3f3f;
int n,m,A,B,dp[maxn][maxn][2][2],d[5][5];
char S[maxn],T[maxn];
int turn(char a)
{
	if(a=='A')
		return 1;
	else if(a=='T')
		return 2;
	else if(a=='G')
		return 3;
	else
		return 4;
}
using std::max;
int main()
{
	scanf("%s",S+1);
	scanf("%s",T+1);
	for(int i=1;i<=4;i++)
		for(int v=1;v<=4;v++)
			scanf("%d",&d[i][v]);
	scanf("%d%d",&A,&B);
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][1][1]=0;
	dp[0][1][0][1]=-A;
	dp[1][0][1][0]=-A;
	n=strlen(S+1);
	m=strlen(T+1);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			dp[i][v][1][1]=max(max(dp[i-1][v-1][1][1],dp[i-1][v-1][1][0]),
					max(dp[i-1][v-1][0][1],dp[i-1][v-1][1][1]))+d[turn(S[i])][turn(T[v])];
			dp[i][v][1][0]=max(dp[i-1][v][1][1]-A,max(dp[i-1][v][1][0]-B,dp[i-1][v][0][1]-A));
			dp[i][v][0][1]=max(dp[i][v-1][1][1]-A,max(dp[i][v-1][0][1]-B,dp[i][v-1][1][0]-A));
		}
	std::cout<<max(dp[n][m][1][1],max(dp[n][m][1][0],dp[n][m][0][1]));
	return 0;
}
