#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll maxn=1e5+5;

ll n,ai[maxn],sum[maxn],L,B;

inline void read(ll &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

ll get(ll l,ll r)
{
	ll mid=l+r>>1,sum1=mid-l,sum2=r-mid;
	return ai[mid]*(mid-l+1)-sum[mid]+sum[l-1]+sum[r]-sum[mid]-ai[mid]*(r-mid);
}

bool check(ll x)
{
	for(ll i=1;i<=n-x+1;i++)
		if(get(i,i+x-1)<=B)
			return true;
	return false;
}

int main()
{
	read(n);
	read(L);
	read(B);
	for(ll i=1;i<=n;i++)
	{
		read(ai[i]);
		sum[i]=sum[i-1]+ai[i];
	}
	ll l=0,r=n,mid,res=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			l=mid+1;
			res=mid;
		}
		else
			r=mid-1;
	}
	std::cout<<res;
	return 0;
}
