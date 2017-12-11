#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e4+5;

struct use
{
	int a,b,v;
	
	bool operator<(const use &tmp)const
	{
		return v<tmp.v;
	}
};

struct use e[maxn*20];

int n,m,x,y,point[maxn],cnt,f[maxn];

double P,S,ans,t;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if(!f[y])
		{
			point[y]=x;
			f[y]=1;
			P+=(double)x*x;
			S+=(double)x;
		}
		else
		{
			e[++cnt]=use{point[y],x,point[y]+x};
			point[y]=x;
		}
	}
	ans=P-(S*S)/(double)n;
	t=S/(double)n;
	std::sort(e+1,e+cnt+1);
	for(int i=1;i<=cnt;i++)
	{
		double t1=P,t2=S,temp;
		t1=(double)(t1-(double)e[i].a*e[i].a+(double)e[i].b*e[i].b);
		t2=(double)(t2-(double)e[i].a+(double)e[i].b);
		temp=(t1-(t2*t2)/(double)n);
		P=t1;
		S=t2;
		if(temp<ans)
		{
			ans=temp;
			t=S/(double)n;
		}
	}
	printf("%.4lf\n",t);
	return 0;
}
