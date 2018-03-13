#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int INF=0x3f3f3f3f;

int T;

ll L,R,out,ans;

void update(ll x,ll v)
{
	if(v<ans)
	{
		ans=v;
		out=x;
	}
	else if(v==ans)
		out=std::min(out,x);
}

inline int get(ll x)
{
	int res=0;
	while(x)
	{
		x/=10;
		++res;
	}
	return res;
}

void check(ll x)
{
	if(x==0)
		return;
	ll tmp=1;
	while(x%10==0&&x)
	{
		x/=10;
		tmp*=10;
	}
	int res=0;
	if(x%10==5)
	{
		int tx=x;
		while(tx)
		{
			tx/=10;
			res++;
		}
		update(x*tmp,res*2-1);
	}
	else
	{
		ll tx=x;
		while(tx)
		{
			tx/=10;
			++res;
		}
		if(x%10<5)
		{
			if((x-(x%10)+5)*tmp<=R)
				update((x-(x%10)+5)*tmp,res*2-1);
			else
				update(x*tmp,res*2);
		}
		else
		{
			if((x-(x%10)+5)*tmp>=L)
				update((x-(x%10)+5)*tmp,res*2-1);
			if((x+10-(x%10)+5)*tmp<=R)
				update((x+10-(x%10)+5)*tmp,get(x+10-(x%10)+5)*2-1);
			update(x*tmp,res*2);
		}
	}
}

int main()
{
	freopen("absurd.in","r",stdin);
	freopen("absurd.out","w",stdout);
	std::cin>>T;
	while(T--)
	{
		ans=INF;
		out=INF;
		std::cin>>L>>R;
		ll tmp=1,now=L;
		while(true)
		{
			while(now<=R&&now%tmp!=0)
				now+=tmp/10;
			if(now>R)
				break;
			check(now);
			tmp*=10;
		}
		std::cout<<out<<std::endl;
	}
	return 0;
}
