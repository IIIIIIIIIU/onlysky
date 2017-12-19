#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=2e5+5;
int n;
ll L,S,hi[maxn],ai[maxn];
inline void read(int &now)
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
bool check(ll mid)
{
	ll res=0;
	for(int i=1;i<=n;i++)
		if(ai[i]*mid+hi[i]>=L)
		{
			res+=ai[i]*mid+hi[i];
			if(res>=S)
				return true;
		}
	return false;
}
int main()
{
	read(n);
	read(S);
	read(L);
	ll l=0,r=1e18,mid,res,t=1e18;
	for(int i=1;i<=n;i++)
		read(hi[i]);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		r=std::min(r,t/ai[i]);
	}
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			res=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	std::cout<<res;
	return 0;
}
