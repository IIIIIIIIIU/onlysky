#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=5e4+5;

int mu[maxn];

bool AntiPrime[maxn];

std::vector<int>primelist;

inline void init()
{
	mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!AntiPrime[i])
		{
			mu[i]=-1;
			primelist.push_back(i);
		}
		for(int j=0,tmp;j<primelist.size();++j)
		{
			tmp=i*primelist[j];
			if(tmp>50000)
				break;
			AntiPrime[tmp]=true;
			if(i%primelist[j]==0)
				break;
			mu[tmp]=-mu[i];
		}
	}
}

inline ll calc(ll val)
{
	ll res=0;
	int lit=std::sqrt(val);
	for(int i=1;i<=lit;i++)
		res+=val/(i*i)*mu[i];
	return res;
}

int main()
{
	int T;
	init();
	std::cin>>T;
	while(T--)
	{
		ll k;
		std::cin>>k;
		ll l=k,r=1644934081;
		while(l<r)
		{
			ll mid=l+r>>1;
			if(calc(mid)>=k)
				r=mid;
			else
				l=mid+1;
		}
		printf("%lld\n",l);
	}
	return 0;
}
