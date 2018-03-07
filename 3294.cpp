#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+9;

int n,m,k,num[15];

ll g[15][35][35],f[15][35][35],C[905][905];

void pre()
{
	C[0][0]=1;
	for(int i=1;i<=900;i++)
	{
		C[i][0]=1;
		for(int v=1;v<=i;v++)
			C[i][v]=(C[i-1][v]+C[i-1][v-1])%mod;
	}
}

int main()
{
	pre();
	std::cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
		std::cin>>num[i];
	for(int i=1;i<=k;i++)
	{
		for(int v=1;v<=n;v++)
			for(int e=1;e<=m;e++)
			{
				if(e*v<num[i]||std::max(e,v)>num[i])
					continue;
				g[i][v][e]=C[v*e][num[i]];
				for(int t=1;t<=v;t++)
					for(int r=1;r<=e;r++)
					{
						if(t==v&&r==e)
							continue;
						(g[i][v][e]-=g[i][t][r]*C[v][t]%mod*C[e][r]%mod)%=mod;
					}
			}
	}
	f[0][0][0]=1;
	for(int i=1;i<=k;i++)
		for(int v=1;v<=n;v++)
			for(int e=1;e<=m;e++)
				for(int t=1;t<=v;t++)
					for(int r=1;r<=e;r++)
						if(g[i][t][r])
							(f[i][v][e]+=f[i-1][v-t][e-r]*g[i][t][r]%mod*C[v][t]%mod*C[e][r]%mod)%=mod;
	ll ans=0;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			(ans+=f[k][i][v]*C[n][i]%mod*C[m][v]%mod)%=mod;
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
