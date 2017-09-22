#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

struct P
{
	ll x,y;
	real angel;
	friend ll operator*(P a,P b)
	{
		return a.x*b.y-a.y*b.x;
	}
	friend P operator-(P a,P b)
	{
		return (P){a.x-b.x,a.y-b.y};
	}
	friend real atan2(P a)
	{
		return atan2(a.y,a.x);
	}
};
struct P a[1505],p[1505];

ll A,B,n;

real ans;

inline void read(ll &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

bool operator<(P a,P b)
{
	return a.angel<b.angel;
}

ll solve(int x)
{
	ll tot=(n-1)*(n-2)*(n-3)/6;
	int top=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=x) p[++top]=a[i];
		else p[0]=a[i];
	}
	for(int i=1;i<=top;i++)
		p[i].angel=atan2(p[i]-p[0]);
	std::sort(p+1,p+top+1);
	int R=2,t=0;
	for(int i=1;i<=top;i++)
	{
		while((p[i]-p[0])*(p[R]-p[0])>=0)
		{
			R=R%top+1;
			++t;
			if(R==i) break;
		}
		tot-=t*(t-1)/2;
		--t;
	}
	return tot;
}

int main()
{
//	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i].x),read(a[i].y);
	if(n==3)
	{
		puts("3.00");
		return 0;
	}
	for(int i=1;i<=n;i++)
		A+=solve(i);
	B=n*(n-1)*(n-2)*(n-3)/24-A;
	ans=2*B+A;
	ans/=n*(n-1)*(n-2)/6;
	printf("%.6lf",ans+3);
	return 0;
}
