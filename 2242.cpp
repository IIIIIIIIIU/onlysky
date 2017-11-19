#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

inline void read(ll &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

ll pow(ll x,ll y,ll z)
{
	ll res=1;
	ll tmp=x;
	while(y)
	{
		if(y&1)
			(res*=tmp)%=z;
		y>>=1;
		(tmp*=tmp)%=z;
	}
	return res;
}

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
	{
		x=1;
		y=0;
	}
	else
	{
		exgcd(b,a%b,y,x);
		y=y-(a/b)*x;
	}
}

ll gcd(int a,int b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}

ll solve(ll a,ll b,ll p)
{
	ll m,v,e=1;
	m=std::ceil(sqrt(p+0.5));
	v=pow(a,p-m-1,p);
	std::map<ll,ll>Map;
	Map[1]=0;
	for(int i=1;i<m;i++)
	{
		e=e*a%p;
		if(!Map.count(e))
			Map[e]=i;
	}
	for(int i=0;i<m;i++)
	{
		if(Map.count(b))
			return (ll)i*m+Map[b];
		b=b*v%p;
	}
	return -1;
}

int main()
{
	ll T,type;
	read(T);
	read(type);
	if(type==1)
	{
		ll x,y,z;
		for(int i=1;i<=T;i++)
		{
			read(x);
			read(y);
			read(z);
			std::cout<<pow(x,y,z)<<std::endl;
		}
	}
	else if(type==2)
	{
		ll a,b,c,x,y,z;
		for(int i=1;i<=T;i++)
		{
			read(a);
			read(c);
			read(b);
			z=gcd(a,b);
			if(c%z!=0)
			{
				puts("Orz, I cannot find x!");
				continue;
			}
			c/=z;
			a/=z;
			b/=z;
			exgcd(a,b,x,y);
			x=(x%b+b)%b;
			std::cout<<(x*c)%b<<std::endl;
		}
	}
	else
	{
		for(int i=1;i<=T;i++)
		{
			ll y,z,p,ans;
			read(y);
			read(z);
			read(p);
			y%=p;
			z%=p;
			if(!y&&!z)
			{
				puts("1");
				continue;
			}
			if(!y)
			{
				puts("Orz, I cannot find x!");
				continue;
			}
			ans=solve(y,z,p);
			if(ans==-1)
				puts("Orz, I cannot find x!");
			else
				std::cout<<ans<<std::endl;
		}
	}
	return 0;
}
