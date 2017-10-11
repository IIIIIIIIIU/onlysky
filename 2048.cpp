#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const real r=0.5772156649,eps=1e-10;

ll n,m;

real ans;

int main()
{
	std::cin>>n>>m;
	if(n<=1000000)
		for(int i=1;i<=n;i++) ans+=0.5/i;
	else
		ans=log(n+1.0)+r,ans/=2.0;
	ans*=m;
	std::cout<<(int)(ans-eps);
	return 0;
}
