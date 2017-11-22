#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

inline void read(ll &now)
{
	char Cget;
	now=0;
	ll if_z=1;
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

ll gcd(ll a,ll b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}

bool can(ll a,ll b,ll d)
{
	return !(a%d)&&!(b%d);
}

int main()
{
	ll T,a,b,x,y,d;
	read(T);
	while(T--)
	{
		read(a);
		read(b);
		read(x);
		read(y);
		if(!a&&!b)
		{
			if(!x&&!y)
				puts("Y");
			else
				puts("N");
		}
		d=gcd(a<<1,b<<1);
		if(can(x,y,d)||can(x+a,y+b,d)||can(x+b,y+a,d)||can(x+a+b,y+a+b,d))
			puts("Y");
		else
			puts("N");
	}
	return 0;
}
