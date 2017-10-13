#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll maxn=10000005;

ll n,m,T,fac[maxn],inv[maxn],phi[maxn],prime[maxn/5],cnt;

int mod;

bool vis[maxn];

inline void read(ll &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

void pre()
{
	fac[0]=fac[1]=inv[1]=phi[1]=1;
	for(int i=2;i<maxn&&i<mod;++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<maxn;++i)
	{
		fac[i]=fac[i-1]*i%mod;
		if(!vis[i]) prime[++cnt]=i,phi[i]=(i-1)*inv[i%mod]%mod;
		if(!phi[i]) phi[i]=phi[i-1];
		else (phi[i]*=phi[i-1])%=mod;
		for(int j=1,k;j<=cnt;++j)
		{
			k=i*prime[j];
			if(k>=maxn) break;
			vis[k]=1;
			if(!(i%prime[j])) break;
		}
	}
}

int main()
{
	read(T);
	std::cin>>mod;
	pre();
	while(T--)
	{
		read(n),read(m);
		printf("%lld\n",phi[m]*fac[n]%mod);
	}
	return 0;
}
