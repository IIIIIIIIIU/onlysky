#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=305;

int sum=0,n,m,ai[maxn][maxn],bi[maxn][maxn];

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

bool get(int r,int c)
{
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			bi[i][v]=0;
	int tmp;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			bi[i][v]+=bi[i-1][v]+bi[i][v-1]-bi[i-1][v-1];
			if(bi[i][v]+ai[i][v]==0)
				continue;
			else if(bi[i][v]+ai[i][v]<0)
				return false;
			else
			{
				tmp=bi[i][v]+ai[i][v];
				bi[i+r][v]+=tmp;
				bi[i][v+c]+=tmp;
				bi[i+r][v+c]-=tmp;
				bi[i][v]-=tmp;
			}
		}
	return true;
}

int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			read(ai[i][v]);
			sum+=ai[i][v];
		}
	int ans=sum;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(sum%(i*v)==0&&get(i,v))
				ans=std::min(ans,sum/(i*v));
	std::cout<<ans;
	return 0;
}
