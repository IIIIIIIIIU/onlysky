#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-6;
const int maxn=5e2+5;

struct point
{
	real x,y;
	
	point(){}
	
	point(real x_,real y_)
	{
		x=x_;
		y=y_;
	}
	
	point operator+(const point &tmp)const
	{
		return point(x+tmp.x,y+tmp.y);
	}
	
	point operator-(const point &tmp)const
	{
		return point(x-tmp.x,y-tmp.y);
	}
	
	real operator*(const point &tmp)const
	{
		return x*tmp.y-y*tmp.x;
	}
	
	point operator*(const real &tmp)const
	{
		return point(x*tmp,y*tmp);
	}
};

struct point p[maxn];

struct line
{
	point p,v;
	
	real alpha;
	
	bool operator<(const line &tmp)const
	{
		return alpha<tmp.alpha;
	}
};

struct line l[maxn],q[maxn];

int n,lcnt,head,tail;

point get_cp(line l1,line l2)
{
	point u=l1.p-l2.p;
	real base=(l2.v*u)/(l1.v*l2.v);
	return l1.p+l1.v*base;
}

bool onlef(point P,line L)
{
	point u=P-L.p;
	return L.v*u>0;
}

void HP()
{
	std::sort(l+1,l+1+lcnt);
	for(int i=1;i<=lcnt;i++)
	{
		for(;tail-head>=2&&!onlef(get_cp(q[tail-1],q[tail-2]),l[i]);tail--);
		if(tail-head>=1&&std::fabs(l[i].alpha-q[tail-1].alpha)<eps)
			q[tail-1]=onlef(q[tail-1].p,l[i])?q[tail-1]:l[i];
		else
			q[tail++]=l[i];
	}
	for(;tail-head>2;)
	{
		if(!onlef(get_cp(q[head],q[head+1]),q[tail-1]))
			head++;
		else if(!onlef(get_cp(q[tail-1],q[tail-2]),q[head]))
			tail--;
		else
			break;
	}
	if(tail-head<=2)
	{
		puts("0.000\n");
		exit(0);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int cnt;
		scanf("%d",&cnt);
		for(int j=1;j<=cnt;j++)
			scanf("%lf%lf",&p[j].x,&p[j].y);
		p[cnt+1]=p[1];
		for(int j=1;j<=cnt;j++)
		{
			++lcnt;
			l[lcnt].p=p[j];
			l[lcnt].v=p[j+1]-p[j];
			l[lcnt].alpha=std::atan2(l[lcnt].v.y,l[lcnt].v.x);
		}
	}
	HP();
	q[tail]=q[head];
	int cnt=0;
	for(int i=head;i<tail;i++)
		p[++cnt]=get_cp(q[i],q[i+1]);
	p[cnt+1]=p[1];
	real ans=0;
	for(int i=1;i<=cnt;i++)
		ans+=p[i]*p[i+1];
	printf("%.3lf\n",ans/2);
	return 0;
}
