#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
int main()
{
	real n;
	std::cin>>n;
	printf("%.9lf\n",(n*(n+1)/2/(2*n-1)));
	return 0;
}
