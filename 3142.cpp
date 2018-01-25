#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
ll n,m,mod,k;
inline ll poww(ll x,ll b)
{
	ll res=1;
	while(b>0)
	{
		if(b&1)
			(res*=x)%=mod;
		b>>=1;
		(x*=x)%=mod;
	}
	return res;
}
int main()
{
	std::cin>>n>>k>>m>>mod;
	if(k==1)
	{
		std::cout<<n%mod;
		return 0;
	}
	n%=mod;
	ll tmp=(m*(m+1)/2)%mod;
	(tmp*=poww(m,k-2))%=mod;
	std::cout<<(n*poww(m,k-1)%mod-tmp*(k-1)%mod+mod)%mod;
	return 0;
}
