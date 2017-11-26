#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e4+5;
const int INF=0x3f3f3f3f;

struct node
{
	int p,val;
	
	node(){}
	
	node(int p_,int val_)
	{
		p=p_;
		val=val_;
	}
};

struct node que[maxn];

int n,m,s,ui[55],di[55],dp[55][maxn<<1];

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
	freopen("order.in","r",stdin);
	freopen("order.out","w",stdout);
//	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(s);
	s<<=1;
	for(int i=1;i<=n;i++)
		read(ui[i]);
	for(int i=1;i<=n;i++)
		read(di[i]);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int v=0;v<=s-ui[i-1];v++)
			dp[i][v]=dp[i-1][v]+v*m;
		int h=0,tail=-1;
		for(int v=s;v>=0;v--)
		{
			int tmp=dp[i][v]-v*di[i];
			while(h<=tail&&que[tail].val>=tmp)
				--tail;
			que[++tail]=node(v,tmp);
		}
		for(int v=s;v>=1;v--)
		{
			while(que[h].p>=v)
				++h;
			dp[i][v]=std::min(dp[i][v],que[h].val+v*di[i]);
		}
		for(int v=0;v<=s-ui[i];v++)
			dp[i][v]=dp[i][v+ui[i]];
		for(int v=s-ui[i]+1;v<=s;v++)
			dp[i][v]=INF;
		for(int v=(s>>1)+1;v<=s;v++)
			dp[i][v]=INF;
	}
	int ans=INF;
	for(int i=0;i<=(s>>1);i++)
		ans=std::min(ans,dp[n][i]+i*m);
	std::cout<<ans;
	return 0;
}
