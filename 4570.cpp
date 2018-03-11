#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-8;
const real INF=1e18;
const int maxn=1e6+5;

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

struct point pi[maxn];

int n,stack[maxn],top;

real ans=INF;

inline bool compare(point a,point b,point c)
{
	return (c-a)*(b-a)<=0;
}

inline real getK(point p1,point p2)
{
	return -(p1.y-p2.y)/(p1.x-p2.x);
}

using std::sqrt;

int main()
{
	freopen("data.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&pi[i].x,&pi[i].y);
	std::sort(pi+1,pi+n+1);
	stack[top=1]=1;
	for(int i=2;i<=n;stack[++top]=i++)
		while(top>1&&compare(pi[stack[top-1]],pi[stack[top]],pi[i]))
			--top;
	int pos=top;
	while(pos>1&&pi[stack[pos-1]].y>=pi[stack[pos]].y)
		--pos;
	point now,pre;
	real k,k1,k2;
	for(int i=pos;i<=top;i++)
	{
		if(i==pos)
			k1=eps;
		else
			k1=getK(pi[stack[i-1]],pi[stack[i]]);
		if(i==top)
			k2=1e12;
		else
			k2=getK(pi[stack[i]],pi[stack[i+1]]);
		now=pi[stack[i]];
		k=sqrt(now.y/now.x);
		if(k<=k1&&k>=k2)
			ans=std::min(ans,k*now.x+now.y/k+now.x+now.y);
		else
			ans=std::min(ans,std::min(k1*now.x+now.y/k1,k2*now.x+now.y/k2)+now.x+now.y);
	}
	printf("%.4lf\n",ans);
	return 0;
}
