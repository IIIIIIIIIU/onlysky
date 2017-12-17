#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+1;
const int maxn=1e5+5;
int n,num,num2[25],ai[25][25];
ll dp[25][1<<12],ans;
bool vis[maxn];
ll solve(int s)
{
	vis[s]=true;
	int last=s;
	num=0;
	for(;last<=n;last<<=1)
	{
		num2[++num]=0;
		int x=last;
		for(;x<=n;x*=3)
		{
			vis[x]=true;
			ai[num][++num2[num]]=x;
		}
	}
	num2[num+1]=0;
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=0;i<=num;i++)
		for(int s1=0;s1<(1<<num2[i]);s1++)
			if(dp[i][s1])
			{
				for(int s2=0;s2<(1<<num2[i+1]);s2++)
					if((!(s1&s2))&&(!(s2&(s2>>1))))
						dp[i+1][s2]=(dp[i+1][s2]+dp[i][s1])%mod;
			}
	return dp[num+1][0];
}
int main()
{
	std::cin>>n;
	ans=1;
	for(int i=1;i<=n;i++)
		if(!vis[i])
			(ans*=solve(i))%=mod;
	std::cout<<ans;
	return 0;
}
