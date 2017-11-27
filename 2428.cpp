#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=1e4+5;
const int INF=0x3f3f3f3f;

int n,m,ai[maxn],sum[maxn],belong[maxn];

real minans=INF,avenue=0;

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

void SA()
{
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++)
	{
		belong[i]=rand()%m+1;
		sum[belong[i]]+=ai[i];
	}
	real ans=0;
	for(int i=1;i<=m;i++)
		ans+=(sum[i]-avenue)*(sum[i]-avenue);
	real T=10000;
	while(T>0.1)
	{
		T*=0.9;
		int t=rand()%n+1,x=belong[t],y;
		if(T>500)
			y=std::min_element(sum+1,sum+m+1)-sum;
		else
			y=rand()%m+1;
		if(x==y)
			continue;
		real tmp=ans;
		ans-=(sum[x]-avenue)*(sum[x]-avenue);
		ans-=(sum[y]-avenue)*(sum[y]-avenue);
		sum[x]-=ai[t];
		sum[y]+=ai[t];
		ans+=(sum[x]-avenue)*(sum[x]-avenue);
		ans+=(sum[y]-avenue)*(sum[y]-avenue);
		if(ans<=tmp)
			belong[t]=y;
		else if(rand()%10000>T)
		{
			sum[x]+=ai[t];
			sum[y]-=ai[t];
			ans=tmp;
		}
		else
			belong[t]=y;
	}
	if(ans<minans)
		minans=ans;
}

int main()
{
	srand(20001024);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		avenue+=ai[i];
	}
	avenue/=m;
	for(int i=1;i<=maxn;i++)
		SA();
	printf("%.2lf\n",sqrt(minans/m));
	return 0;
}
