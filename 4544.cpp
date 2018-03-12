#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll n,pi[21],ans;

inline ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}

int main()
{
	int T;
	std::cin>>T;
	while(T--)
	{
		std::cin>>n;
		ll N=n<<1;
		for(ll d=1;d*d<=N;d++)
		{
			if(N%d!=0)
				continue;
			ll lit=N/d,t;
			for(ll a=1,b;a*a*3<=lit;a++)
			{
				if(a*a*6==lit)
					continue;
				b=lit-a*a*3;
				t=std::sqrt(b);
				if(t*t==b&&gcd(b,a*a*3)==1)
					ans++;
			}
			if(d*d*2==N)
				continue;
			lit=d;
			for(ll a=1,b;a*a*3<=lit;a++)
			{
				if(a*a*6==lit)
					continue;
				b=lit-a*a*3;
				t=std::sqrt(b);
				if(t*t==b&&gcd(b,a*a*3)==1)
					ans++;
			}
		}
		std::cout<<ans*4+2<<std::endl;
		ans=0;
	}
	return 0;
}
