#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=2e3+5;
int n,m,wi[maxn];
ll f[maxn][maxn],fac[maxn],inv[maxn];
inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		e>>=1;
		x=x*x%mod;
	}
	return res;
}
ll C(ll x,ll y)
{
	if(y>x)
		return 0;
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>n>>m;
	for(int i=1;i<=m;i++)
		std::cin>>wi[i];
	for(int i=0;i<=n;i++)
		f[0][i]=1;
	fac[0]=1;
	inv[0]=1;
	for(int i=1;i<=2000;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=inv[i-1]*poww(i,mod-2)%mod;
	}
	for(int i=0;i<=n;i++)
		f[0][i]=1;
	for(int i=1;i<=m;i++)
		for(int v=1;v<=n;v++)
			f[i][v]=f[i-1][v]*C(v+wi[i]-1,v-1)%mod;
	ll ans=0;
	for(int i=0,base=1;i<=n;i++,base=-base)
		(ans+=base*C(n,i)*f[m][n-i]%mod)%=mod;
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
