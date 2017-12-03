#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real two=2.00;
const real INF=1e15;
const real eps=1e-9;
const real four=4.00;
const int maxn=2e5+5;

struct point
{
	real x,y;
};

struct point p[maxn],now[maxn];

int n,tot;

real po[maxn];

bool cmpx(const point &a,const point &b)
{
	return a.x<b.x;
}

bool cmpy(const point &a,const point &b)
{
	return a.y<b.y;
}

real dis(const point &a,const point &b)
{
	real X=a.x-b.x;
	real Y=a.y-b.y;
	return std::sqrt(X*X+Y*Y);
}

real solve(int l,int r)
{
	if(r-l<2)
		return INF;
	if(r-l==2)
		return dis(p[l],p[l+1])+dis(p[l],p[r])+dis(p[l+1],p[r]);
	int mid=l+r>>1;
	real d1=solve(l,mid);
	real d2=solve(mid+1,r);
	real d=std::min(d1,d2),res=d;
	tot=0;
	for(int i=l;i<=r;i++)
		if(std::fabs(p[i].x-p[mid].x)<=d/four)
			now[++tot]=p[i];
	std::sort(now+1,now+tot+1,cmpy);
	for(int i=1;i<=tot;i++)
		for(int j=i+1;j<=tot;j++)
		{
			if(now[j].y-now[i].y>d/two+eps)
				break;
			for(int k=j+1;k<=tot;k++)
			{
				if(now[k].y-now[i].y>d/two+eps)
					break;
				res=std::min(res,dis(now[i],now[j])+dis(now[i],now[k])+dis(now[j],now[k]));
			}
		}
	return res;
}

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	std::sort(p+1,p+n+1,cmpx);
	printf("%.6lf",solve(1,n));
	return 0;
}
