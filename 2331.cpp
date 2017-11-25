#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e2+5;
const int maxs=1e5+5;
const int mod=20110520;

int n,m,has[maxn][maxn],bit[15];

ll dp[2][maxs][3];

char map[maxn][maxn];

inline int get(int S,int pos,int v)
{
	return S-(S/bit[pos]%3)*bit[pos]+v*bit[pos];
}

void print(int r,int c,int now)
{
	for(int i=0;i<=bit[m+1]-1;i++)
		for(int v=0;v<3;v++)
			if(dp[now][i][v])
				printf("%d %d %d %d %d\n",r,c,i,v,dp[now][i][v]);
}

int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%s",map[i]+1);
	if(n>=m)
	{
		for(int i=1;i<=n;i++)
			for(int v=1;v<=m;v++)
				if(map[i][v]=='_')
					has[i][v]=true;
	}
	else
	{
		for(int i=1;i<=n;i++)
			for(int v=1;v<=m;v++)
				if(map[i][v]=='_')
					has[v][i]=true;
		std::swap(n,m);
	}
	if(m==1)
	{
		printf("0\n");
		return 0;
	}
	int now=1,last=0;
	dp[0][0][0]=1;
	bit[1]=1;
	for(int i=2;i<=14;i++)
		bit[i]=bit[i-1]*3;
	int S=bit[m+1]-1;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			memset(dp[now],0,sizeof(dp[now]));
			if(v==1)
			{
				for(int s=0;s<=S;s++)
				{
					int d=s/bit[v]%3;
					if(has[i][v])
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,2)][0])%=mod;
							(dp[now][s][1]+=dp[last][get(s,v,0)][0])%=mod;
							(dp[now][s][2]+=dp[last][get(s,v,1)][0])%=mod;
						}
						else if(d==1)
						{
							(dp[now][s][0]+=dp[last][get(s,v,1)][0]+dp[last][get(s,v,0)][0])%=mod;
						}
						else
						{
							(dp[now][s][0]+=dp[last][get(s,v,2)][0])%=mod;
							(dp[now][s][2]+=dp[last][get(s,v,0)][0])%=mod;
						}
					}
					else
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][0])%=mod;
						}
					}
				}
			}
			else if(v==m)
			{
				for(int s=0;s<=S;s++)
				{
					int d=s/bit[v]%3;
					if(has[i][v])
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,1)][1]+dp[last][get(s,v,2)][0]+dp[last][get(s,v,0)][2])%=mod;
						}
						else if(d==1)
						{
							(dp[now][s][0]+=dp[last][get(s,v,1)][0]+dp[last][get(s,v,0)][0])%=mod;
						}
						else
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][1]+dp[last][get(s,v,2)][0])%=mod;
						}
					}
					else
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][0])%=mod;
						}                                   
					}
				}
			}
			else
			{
				for(int s=0;s<=S;s++)
				{
					int d=s/bit[v]%3;
					if(has[i][v])
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,1)][1]+dp[last][get(s,v,2)][0]+dp[last][get(s,v,0)][2])%=mod;
							(dp[now][s][1]+=dp[last][get(s,v,0)][0]+dp[last][get(s,v,0)][1])%=mod;
							(dp[now][s][2]+=dp[last][get(s,v,1)][0]+dp[last][get(s,v,0)][2])%=mod;
						}
						else if(d==1)
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][0]+dp[last][get(s,v,1)][0])%=mod;
						}
						else if(d==2)
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][1]+dp[last][get(s,v,2)][0])%=mod;
							(dp[now][s][2]+=dp[last][get(s,v,0)][0])%=mod;
						}
					}
					else
					{
						if(d==0)
						{
							(dp[now][s][0]+=dp[last][get(s,v,0)][0])%=mod;
						}
					}
				}
			}
//			print(i,v,now);
			now^=1;
			last^=1;
		}
	std::cout<<dp[last][0][0];
	return 0;
}
