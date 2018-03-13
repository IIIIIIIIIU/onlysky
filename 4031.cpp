#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const int mod=1e9;
const int maxn=1e2+5;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};

int n,m,num,id[maxn][maxn];

char str[maxn][maxn];

ll A[maxn][maxn],B[maxn][maxn],D[maxn][maxn];

int main()
{
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		std::cin>>str[i]+1;
		for(int v=1;v<=m;v++)
			if(str[i][v]=='.')
				id[i][v]=++num;
	}
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(id[i][v])
			{
				int x,y;
				for(int e=0;e<4;e++)
				{
					x=i+dx[e];
					y=v+dy[e];
					if(x>0&&x<=n&&y>0&y<=m&&id[x][y])
					{
						A[id[i][v]][id[i][v]]++;
						B[id[i][v]][id[x][y]]++;
					}
				}
			}
	for(int i=1;i<=num;i++)
		for(int v=1;v<=num;v++)
			D[i][v]=A[i][v]-B[i][v];
	num--;
	int f=1;
	for(int i=1;i<=num;i++)
	{
		for(int v=i+1;v<=num;v++)
		{
			while(D[v][i]!=0)
			{
				ll t=D[i][i]/D[v][i];
				std::swap(D[i],D[v]);
				for(int e=i;e<=num;e++)
					(D[v][e]=D[v][e]-D[i][e]*t%mod+mod)%=mod;
				f=-f;
			}
		}
	}
	ll ans=1;
	for(int i=1;i<=num;i++)
		ans=(ans*D[i][i])%mod;
	ans*=f;
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
