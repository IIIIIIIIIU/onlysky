#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e6+5;

ll n,mod,size[maxn<<1],dp[maxn],fac[maxn]={1,1},I[maxn]={1,1},inv[maxn]={1,1};

ll C(ll x,ll y)
{
	if(x<y) return 0;
	if(x<mod&&y<mod)
		return fac[x]*inv[y]%mod*inv[x-y]%mod;
	return C(x/mod,y/mod)*C(x%mod,y%mod)%mod;
}

int main()
{
	std::cin>>n>>mod;
	for(int i=2;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		I[i]=(mod-mod/i)*I[mod%i]%mod;
		inv[i]=inv[i-1]*I[i]%mod;
	}
	for(int i=n;i>=1;i--)
	{
		size[i]=size[i<<1]+size[i<<1|1]+1;
		dp[i]=C(size[i]-1,size[i<<1])*((i<<1)>n?1:dp[i<<1])%mod*((i<<1|1)>n?1:dp[i<<1|1])%mod;
	}
	std::cout<<dp[1];
	return 0;
}
