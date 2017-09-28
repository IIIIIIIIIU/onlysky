#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

int n;

ll ans=0;

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++) ans+=n/i;
	std::cout<<ans;
	return 0;
}
