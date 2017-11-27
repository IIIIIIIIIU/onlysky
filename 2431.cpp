#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll mod=10000;
const ll maxn=1e3+5;

ll n,k,f[maxn][maxn],sum[maxn];

inline void read(ll &now)
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
	read(n);
	read(k);
	f[1][0]=1;
	for(ll i=2;i<=n;i++)
	{
		sum[0]=f[i-1][0];
		for(ll v=1;v<=k;v++)
			(sum[v]=sum[v-1]+f[i-1][v])%=mod;
		for(ll v=0,lit;v<=k;v++)
		{
			lit=std::max(v-i+1,0LL);
			if(lit)
				(f[i][v]=sum[v]-sum[lit-1])%=mod;
			else
				f[i][v]=sum[v];
		}
	}
	std::cout<<(f[n][k]+mod)%mod;
	return 0;
}
