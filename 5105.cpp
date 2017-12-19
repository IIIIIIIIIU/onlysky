#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
ll a,b,c;
ll gcd(ll a,ll b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
int main()
{
	std::cin>>a>>b>>c;
	b=a*b/gcd(a,b);
	c=b*c/gcd(b,c);
	std::cout<<c;
	return 0;
}
