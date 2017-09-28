#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll n,m,l,p;

ll mul(ll x,ll y,ll mod)
{
	ll res=0;
	while(y)
	{
		if(y&1) (res+=x)%=mod;
		(x<<=1)%=mod;
		y>>=1;
	}
	return res;
}

ll pow(ll x,ll y,ll mod)
{
	ll res=1;
	while(y)
	{
		if(y&1) res=mul(res,x,mod);
		x=mul(x,x,mod);
		y>>=1;
	}
	return res;
}

int main()
{
	std::cin>>n>>m>>l;
	p=n/2+1,p=pow(p,m,n+1);
	std::cout<<mul(p,l,n+1);
	return 0;
}
