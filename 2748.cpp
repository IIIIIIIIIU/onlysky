#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e3+5;
int n,s,lit;
bool dp[55][maxn];
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
int main()
{
	read(n);
	read(s);
	read(lit);
	dp[0][s]=true;
	for(int i=1,x,v;i<=n;i++)
	{
		read(x);
		for(v=x;v<=lit;v++)
			dp[i][v]|=dp[i-1][v-x];
		for(v=lit-x;v>=0;v--)
			dp[i][v]|=dp[i-1][v+x];
	}
	for(int i=lit;i>=0;i--)
		if(dp[n][i])
		{
			printf("%d\n",i);
			return 0;
		}
	puts("-1");
	return 0;
}
