#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll n,ans,lit;

ll phi(ll x)
{
	ll t=x;
	for(ll i=2;i<=lit;i++)
		if(x%i==0)
		{
			t=t/i*(i-1);
			while(x%i==0)
				x/=i;
		}
	if(x>1)
		t=t/x*(x-1);
	return t;
}

int main()
{
	std::cin>>n;
	lit=std::sqrt(n);
	for(int i=1;i<=lit;i++)
		if(n%i==0)
		{
			ans+=phi(n/i)*i;
			if(n/i!=i)
				ans+=phi(i)*(n/i);
		}
	std::cout<<ans;
	return 0;
}
