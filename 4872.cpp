#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e5+3;
const int maxn=1e5+5;

int n,k,ai[maxn],num;

ll bi[maxn];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		x=x*x%mod;
		e>>=1;
	}
	return res;
}

int main()
{
	std::cin>>n>>k;
	for(int i=1;i<=n;i++)
		std::cin>>ai[i];
	for(int i=n;i>=1;i--)
		if(ai[i])
		{
			num++;
			for(int v=1;v*v<=i;v++)
				if(i%v==0)
				{
					ai[v]^=1;
					if(i/v!=v)
						ai[i/v]^=1;
				}
		}
	for(int i=n;i>=1;i--)
		bi[i]=(bi[i+1]*(n-i)%mod+n)%mod*poww(i,mod-2)%mod;
	ll ans=0;
	if(k>num)
		ans=num;
	else
	{
		for(int i=num;i>k;i--)
			ans=(ans+bi[i])%mod;
		ans=(ans+k)%mod;
	}
	for(int i=1;i<=n;i++)
		ans=(ans*i)%mod;
	std::cout<<ans<<std::endl;
	return 0;
}
