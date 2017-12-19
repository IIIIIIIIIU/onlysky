#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const int maxm=1e5+5;
struct node
{
	int pos,val;
	bool operator<(const node &tmp)const
	{
		return pos<tmp.pos;
	}
};
struct node ai[maxm];
int n,m,dp[maxm][2],g[maxm];
ll ans;
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
using std::min;
ll solve(int x)
{
	for(int i=1;i<=m;i++)
		if(ai[i].val&x)
			g[i]=1;
		else
			g[i]=0;
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1,tmp;i<=m;i++)
	{
		tmp=ai[i].pos-ai[i-1].pos-1;
		if(tmp)
		{
			if(g[i])
			{
				dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]+1);
				dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]+1);
			}
			else
			{
				dp[i][1]=min(dp[i-1][0]+2,dp[i-1][1]+2);
				dp[i][0]=min(dp[i-1][0],dp[i-1][1]);
			}
		}
		else
		{
			if(g[i])
			{
				dp[i][1]=dp[i-1][0]+1;
				dp[i][0]=dp[i-1][1];
			}
			else
			{
				dp[i][1]=dp[i-1][1]+1;
				dp[i][0]=dp[i-1][0];
			}
		}
	}
	ll res=min(dp[m][0],dp[m][1]);
	return res;
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=m;i++)
	{
		read(ai[i].pos);
		read(ai[i].val);
	}
	std::sort(ai+1,ai+m+1);
	for(int i=0;i<=30;i++)
		ans+=solve(1<<i)*(1<<i);
	std::cout<<ans;
	return 0;
}
