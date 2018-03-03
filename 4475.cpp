#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
ll n,k;
int main()
{
	std::cin>>n>>k;
	ll ans=1,x=2;
	n*=k;
	while(n>0)
	{
		if(n&1)
			ans=ans*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	std::cout<<ans<<std::endl;
	return 0;
}
