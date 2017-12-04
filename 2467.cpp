#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int mod=2007;

int n;

int pow(int base,int e)
{
	int res=1;
	while(e>0)
	{
		if(e&1)
			(res*=base)%=mod;
		(base*=base)%=mod;
		e>>=1;
	}
	return res;
}

int main()
{
	int T;
	std::cin>>T;
	for(int i=1;i<=T;i++)
	{
		std::cin>>n;
		std::cout<<4*n*pow(5,n-1)%mod<<std::endl;
	}
	return 0;
}
