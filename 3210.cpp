#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;

int n,xi[maxn],yi[maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

inline ll solve(int x,int y)
{
	ll res=0;
	for(int i=1;i<=n;i++)
		res+=std::abs(x-xi[i])+std::abs(y-yi[i]);
	return res;
}

int main()
{
	read(n);
	for(int i=1,x,y;i<=n;i++)
	{
		read(x);
		read(y);
		xi[i]=x+y;
		yi[i]=x-y;
	}
	std::sort(xi+1,xi+n+1);
	std::sort(yi+1,yi+n+1);
	int x=xi[n+1>>1],y=yi[n+1>>1];
	if(~(x^y)&1)
		std::cout<<solve(x,y)/2<<std::endl;
	else
		std::cout<<std::min(std::min(solve(x-1,y),solve(x+1,y)),std::min(solve(x,y-1),solve(x,y+1)))/2<<std::endl;
	return 0;
}
