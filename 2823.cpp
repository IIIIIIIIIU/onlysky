#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
typedef double real;
const real eps=1e-6;
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
};
struct point ai[maxn];
struct cir
{
	real x,y,r;
	cir(){}
	cir(real x_,real y_,real r_)
	{
		x=x_;
		y=y_;
		r=r_;
	}
	void out()
	{
		printf("%.2lf %.2lf %.2lf\n",x,y,r);
	}
};
int n;
real dist(point x,point y)
{
	return std::sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
bool dist(cir x,point y)
{
	return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)>x.r*x.r+eps;
}
cir makeit(point a,point b,point c)
{
	real x,y;
	real ax=a.x*a.x,ay=a.y*a.y,bx=b.x*b.x,by=b.y*b.y,cx=c.x*c.x,cy=c.y*c.y;
	real l1=ax-bx+ay-by,l2=ax-cx+ay-cy,r1=2*a.x-2*b.x,r2=2*a.y-2*b.y;
	real r3=2*a.x-2*c.x,r4=2*a.y-2*c.y;
	x=(l1-r2/r4*l2)/(r1-r2/r4*r3);
	y=(l1-r1/r3*l2)/(r2-r1/r3*r4);
	if(r4==0)
		x=(a.x+c.x)/2;
	if(r3==0)
		y=(a.y+c.y)/2;
	return cir(x,y,dist(point(x,y),a));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&ai[i].x,&ai[i].y);
		std::swap(ai[i],ai[rand()%i+1]);
	}
	cir base=cir(ai[1].x,ai[1].y,0);
	for(int i=1;i<=n;i++)
		if(dist(base,ai[i]))
		{
			base=cir(ai[i].x,ai[i].y,0);
			for(int v=1;v<i;v++)
				if(dist(base,ai[v]))
				{
					base=cir((ai[i].x+ai[v].x)/2,(ai[i].y+ai[v].y)/2,dist(ai[i],ai[v])/2);
					for(int k=1;k<v;k++)
					{
						if(dist(base,ai[k]))
						{
							base=makeit(ai[i],ai[v],ai[k]);
						}
					}
				}
		}
	base.out();
	return 0;
}
