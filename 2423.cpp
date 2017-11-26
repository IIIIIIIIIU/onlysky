#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int mod=1e8;
const int maxn=5e3+5;

int n,m,f[2][maxn],g[2][maxn];

char str1[maxn],str2[maxn];

int main()
{
	scanf("%s",str1+1);
	scanf("%s",str2+1);
	n=strlen(str1+1)-1;
	m=strlen(str2+1)-1;
	for(int i=0;i<=m;i++)
		g[0][i]=1;
	g[1][0]=1;
	int mar=0;
	for(int i=1;i<=n;i++)
	{
		mar^=1;
		for(int j=1;j<=m;j++)
		{
			if(str1[i]==str2[j])
			{
				f[mar][j]=f[mar^1][j-1]+1;
				g[mar][j]=g[mar^1][j-1];
				g[mar][j]+=(f[mar][j]==f[mar][j-1])*g[mar][j-1];
				g[mar][j]+=(f[mar][j]==f[mar^1][j])*g[mar^1][j];
			}
			else
			{
				f[mar][j]=std::max(f[mar^1][j],f[mar][j-1]);
				g[mar][j]=(f[mar][j]==f[mar^1][j])*g[mar^1][j];
				g[mar][j]+=(f[mar][j]==f[mar][j-1])*g[mar][j-1];
				g[mar][j]-=(f[mar^1][j-1]==f[mar][j])*g[mar^1][j-1];
			}
			g[mar][j]%=mod;
		}
	}
	g[mar][m]+=mod;
	g[mar][m]%=mod;
	printf("%d\n%d",f[mar][m],g[mar][m]);
	return 0;
}
