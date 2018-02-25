#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e3+5;
int n,m,g[maxn][maxn],T;
ll f[maxn][maxn];
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
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		for(int i=1;i<=n;i++)
		{
			for(int v=1;v<=m;v++)
				read(g[i][v]);
			for(int v=m;v>=1;v--)
				f[i][v]=std::max(f[i-1][v+1]+g[i][v],std::max(f[i-1][v],f[i][v+1]));
		}
		std::cout<<f[n][1]<<std::endl;
	}
	return 0;
}
