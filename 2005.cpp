#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll f[100005],n,m;

int main()
{
	std::cin>>n>>m;
	int tmp=std::min(n,m);
	ll ans=0;
	for(int i=tmp;i>=1;i--)
	{
		f[i]=(ll)(m/i)*(n/i);
		for(int j=i+i;j<=tmp;j+=i)
			f[i]-=f[j];
		ans+=f[i]*(2*i-1);
	}
	std::cout<<ans;
	return 0;
}
