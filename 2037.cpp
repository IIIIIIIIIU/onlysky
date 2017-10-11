#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=1005,INF=0x3f3f3f3f;

struct NodeType
{
	int x,y,v;

	bool operator<(const NodeType &tmp)const
	{
		return x<tmp.x;
	}
};

struct NodeType seq[maxn],ail[maxn],air[maxn];

int n,x0,nl,nr;

real dp[maxn][maxn][2],sumr[maxn],suml[maxn],all;

inline void read(int &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now=now*if_z;
}

real cost(int i,int j)
{
	return (suml[nl]-suml[i]+sumr[nr]-sumr[j])/1000;
}

int main()
{
//	freopen("sueball.in","r",stdin);
//	freopen("sueball.out","w",stdout);
	read(n),read(x0);
	for(int i=1;i<=n;i++)
		read(seq[i].x);
	for(int i=1;i<=n;i++)
		read(seq[i].y),all+=seq[i].y;
	for(int i=1;i<=n;i++)
		read(seq[i].v);
	std::sort(seq+1,seq+n+1);
	nl=0;
	for(int i=1;i<=n;i++)
		if(seq[i].x<=x0) nl++;
		else break;
	nr=n-nl;
	for(int i=1;i<=nl;i++)
		ail[i]=seq[nl-i+1],suml[i]=suml[i-1]+ail[i].v;
	for(int i=1;i<=nr;i++)
		air[i]=seq[nl+i],sumr[i]=sumr[i-1]+air[i].v;
	air[0].x=x0,ail[0].x=x0;
	dp[0][0][0]=dp[0][0][1]=0;
	for(int i=0;i<=nl;i++)
		for(int j=0;j<=nr;j++)
		{
			if(!i&&!j) continue;
			dp[i][j][0]=dp[i][j][1]=INF;
			if(i) dp[i][j][0]=std::min(dp[i-1][j][0]+(ail[i-1].x-ail[i].x)*cost(i-1,j),dp[i][j][0]);
			if(i) dp[i][j][0]=std::min(dp[i-1][j][1]+(air[j].x-ail[i].x)*cost(i-1,j),dp[i][j][0]);
			if(j) dp[i][j][1]=std::min(dp[i][j-1][1]+(air[j].x-air[j-1].x)*cost(i,j-1),dp[i][j][1]);
			if(j) dp[i][j][1]=std::min(dp[i][j-1][0]+(air[j].x-ail[i].x)*cost(i,j-1),dp[i][j][1]);
			dp[i][j][0]=std::min(dp[i][j][1]+(air[j].x-ail[i].x)*cost(i,j),dp[i][j][0]);
			dp[i][j][1]=std::min(dp[i][j][0]+(air[j].x-ail[i].x)*cost(i,j),dp[i][j][1]);
		}
	printf("%.3lf\n",all/1000-std::min(dp[nl][nr][0],dp[nl][nr][1]));
	return 0;
}
