#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e3+5;
typedef double real;
const real eps=1e-9;
int n,m,f[maxn];
real sum[maxn];
int find(int x)
{
	if(f[x]==x)
		return x;
	int t=find(f[x]);
	sum[x]*=sum[f[x]];
	f[x]=t;
	return f[x];
}
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
int main()
{
	int T;
	read(T);
	for(int t=1;t<=T;t++)
	{
		read(n);
		read(m);
		for(int i=1;i<=n;i++)
		{
			f[i]=i;
			sum[i]=1;
		}
		bool pd=false;
		for(int i=1;i<=m;i++)
		{
			int u,v,x,y;
			read(u);
			read(v);
			read(x);
			read(y);
			int r1=find(u);
			int r2=find(v);
			if(r1!=r2)
			{
				f[r2]=r1;
				sum[r2]*=sum[u]/sum[v]*(real)y/x;
			}
			else if(std::fabs((real)(sum[u]/sum[v])-((real)x/(real)y))>eps)
					pd=true;
		}
		printf("Case #%d: ",t);
		if(pd)
			puts("No");
		else
			puts("Yes");
	}
	return 0;
}
