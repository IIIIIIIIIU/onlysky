#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e3+5;
const int mod=2011;

struct node
{
	int h,b;
};

struct node ai[maxn];

int n,t[maxn],dp[maxn][maxn];

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

inline bool cmp1(const node &a,const node &b)
{
	if(a.h==b.h)
		return a.b<b.b;
	return a.h>b.h;
}

int solve(int l,int r)
{
	memset(dp[l-1],0,sizeof(dp[l-1]));
	dp[l-1][0]=1;
	for(int i=l;i<=r;i++)
	{
		dp[i][0]=dp[i-1][0];
		for(int v=1;v<=ai[i].b&&v<l;v++)
			dp[i][v]=(dp[i][v-1]+dp[i-1][v])%mod;
	}
	int res=0;
	for(int i=0;i<=ai[r].b&&i<l;i++)
		res=(res+dp[r][i])%mod;
	return res;
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(ai[i].h);
		read(ai[i].b);
		ai[i].b--;
	}
	std::sort(ai+1,ai+n+1,cmp1);
	int ans1=1,ans2=1;
	for(int i=1;i<=n;i++)
	{
		if(ai[i].h==ai[i-1].h)
			t[i]=t[i-1]+1;
		(ans1*=(std::min(i-t[i],ai[i].b+1)+t[i])%mod)%=mod;
	}
	for(int l=1,r;l<=n;l=r+1)
	{
		r=l;
		while(r<n&&ai[r+1].h==ai[l].h)
			++r;
		(ans2*=solve(l,r))%=mod;
	}
	std::cout<<ans1<<' '<<ans2<<std::endl;
	return 0;
}
