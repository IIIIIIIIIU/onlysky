#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;
const int maxn=1e3+5;

ll n,m,f[maxn],fac[maxn],inv[maxn];

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

inline ll C(int a,int b)
{
	if(b>a)
		return 0;
	if(!b||b==a)
		return 1;
	return fac[a]*inv[b]%mod*inv[a-b]%mod;
}

int main()
{
	std::cin>>n>>m;
	fac[1]=inv[1]=1;
	for(int i=2;i<=m;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=inv[i-1]*poww(i,mod-2)%mod;
	}
	if(m==1)
	{
		std::cout<<n*(n+1)%mod*poww(2,mod-2)%mod<<std::endl;
		return 0;
	}
	else
		f[0]=m*(1-poww(m,n))%mod*poww(1-m,mod-2)%mod;
	for(int i=1;i<=m;i++)
	{
		f[i]=poww(n,i)*poww(m,n+1)%mod;
		for(int v=0;v<i;v++)
			(f[i]+=C(i,v)*f[v]%mod*poww(-1,(i-v)%2)%mod)%=mod;
		(f[i]*=poww(m-1,mod-2))%=mod;
	}
	std::cout<<(f[m]+mod)%mod<<std::endl;
	return 0;
}
