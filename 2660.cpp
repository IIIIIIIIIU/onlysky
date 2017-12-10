#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e2+5;

typedef long long ll;

int q[maxn];

ll n,f[maxn],dp[maxn][2];

int main()
{
	int i;
	std::cin>>n;
	f[1]=1;
	f[2]=2;
	for(i=3;f[i-1]+f[i-2]<=n;++i)
		f[i]=f[i-1]+f[i-2];
	int tp=0;
	for(i--;i&&n;i--)
		if(n>=f[i])
		{
			q[++tp]=i;
			n-=f[i];
		}
	dp[tp][1]=1;
	dp[tp][0]=(q[tp]-1)>>1;
	for(i=tp-1;i;i--)
	{
		dp[i][1]=dp[i+1][0]+dp[i+1][1];
		dp[i][0]=dp[i+1][0]*((q[i]-q[i+1])>>1)+dp[i+1][1]*((q[i]-q[i+1]-1)>>1);
	}
	printf("%lld\n",dp[1][0]+dp[1][1]);
	return 0;
}
