#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll maxn=1e5+5;

ll n,xi[maxn],yi[maxn],sumx[maxn],sumy[maxn];
ll basex[maxn],basey[maxn],ans;

inline ll get(ll x)
{
	ll res=0;
	ll pos=std::lower_bound(xi+1,xi+n+1,basex[x])-xi;
	res+=basex[x]*pos-sumx[pos]+sumx[n]-sumx[pos]-basex[x]*(n-pos);
	pos=std::lower_bound(yi+1,yi+n+1,basey[x])-yi;
	res+=basey[x]*pos-sumy[pos]+sumy[n]-sumy[pos]-basey[x]*(n-pos);
	return res;
}

int main()
{
	std::cin>>n;
	for(ll i=1,x,y;i<=n;i++)
	{
		std::cin>>x>>y;
		basex[i]=xi[i]=x+y;
		basey[i]=yi[i]=x-y;
	}
	std::sort(xi+1,xi+n+1);
	std::sort(yi+1,yi+n+1);
	for(ll i=1;i<=n;i++)
	{
		sumx[i]=sumx[i-1]+xi[i];
		sumy[i]=sumy[i-1]+yi[i];
	}
	ans=2e18;
	for(ll i=1;i<=n;i++)
		ans=std::min(ans,get(i));
	std::cout<<(ans>>1)<<std::endl;
	return 0;
}
