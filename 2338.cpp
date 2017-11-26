#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1505;

struct point
{
	ll x,y;
	
	point(){}
	
	point(ll x_,ll y_)
	{
		x=x_;
		y=y_;
	}
	
	ll operator*(const point &tmp)const
	{
		return x*tmp.y-tmp.x*y;
	}
	
	point operator-(const point &tmp)const
	{
		return point(x-tmp.x,y-tmp.y);
	}
	
	point operator+(const point &tmp)const
	{
		return point(x+tmp.x,y+tmp.y);
	}
	
	ll operator&(const point &tmp)const
	{
		return (tmp.x-x)*(tmp.x-x)+(y-tmp.y)*(y-tmp.y);
	}
	
	bool operator==(const point &tmp)const
	{
		return x==tmp.x&&y==tmp.y;
	}
	
	bool operator<(const point &tmp)const
	{
		if(x==tmp.x)
			return y<tmp.y;
		return x<tmp.x;
	}
};

struct point bi[maxn];

struct line
{
	point a,b,c;
	
	ll len;
	
	void make()
	{
		c=a+b;
		len=a&b;
	}
	
	bool operator<(const line &tmp)const
	{
		if(c==tmp.c)
			return len<tmp.len;
		return c<tmp.c;
	}
	
	bool operator==(const line &tmp)const
	{
		return c==tmp.c&&len==tmp.len;
	}
	
	ll operator*(const line &tmp)const
	{
		ll cur=(a-tmp.a)*(b-tmp.a);
		if(cur<0)
			return -cur;
		return cur;
	}
};

struct line ai[maxn*maxn];

int n,cnt;

ll ans;

inline void read(int &now)
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

int main()
{
	freopen("crectangle.in","r",stdin);
	freopen("crectangle.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(bi[i].x);
		read(bi[i].y);
	}
	for(int i=1;i<=n;i++)
		for(int v=i+1;v<=n;v++)
		{
			++cnt;
			ai[cnt].a=bi[i];
			ai[cnt].b=bi[v];
			ai[cnt].make();
		}
	std::sort(ai+1,ai+cnt+1);
	for(int i=1;i<=cnt;i++)
		for(int v=i-1;v>=1;v--)
			if(ai[i]==ai[v])
				ans=std::max(ai[i]*ai[v],ans);
			else break;
	std::cout<<ans;
	return 0;
}
