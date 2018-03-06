#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const real eps=1e-6;
const ll maxn=1e5+5;

struct point
{
	real x,y;
	
	point(){}
	
	point(real x_,real y_)
	{
		x=x_;
		y=y_;
	}
	
	inline bool operator<(const point &tmp)const
	{
		return x<tmp.x;
	}
	
	inline point operator-(const point &tmp)const
	{
		return point(x-tmp.x,y-tmp.y);
	}
	
	inline real operator*(const point &tmp)const
	{
		return x*tmp.y-y*tmp.x;
	}
};

struct point ai[maxn];

ll n,d,stack[maxn],top;

real sum[maxn],xi[maxn];

inline bool compare(point a,point b,point c)
{
	return (a-c)*(b-c)>=0;
}

inline real get(ll a,ll b)
{
	return (sum[a]-sum[b-1])/(xi[a]+a*d-b*d);
}

inline real solve(ll now)
{
	ll l=1,r=top,mid1,mid2;
	while(r-l>3)
	{
		mid1=l+(r-l)/3;
		mid2=r-(r-l)/3;
		if(get(now,stack[mid1])>=get(now,stack[mid2])+eps)
			r=mid2;
		else
			l=mid1;
	}
	real ans=0;
	for(ll i=l;i<=r;i++)
		ans=std::max(ans,get(now,stack[i]));
	return ans;
}

int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>n>>d;
	real ans=0;
	for(ll i=1;i<=n;i++)
	{
		std::cin>>sum[i]>>xi[i];
		sum[i]+=sum[i-1];
		ai[i].x=i*d;
		ai[i].y=sum[i-1];
		while(top>1&&compare(ai[i],ai[stack[top]],ai[stack[top-1]]))
			--top;
		stack[++top]=i;
		ans+=solve(i);
	}
	std::cout<<(ll)(ans+0.5)<<std::endl;
	return 0;
}
