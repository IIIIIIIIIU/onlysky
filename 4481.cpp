#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long double Real;

const int maxn=5e5+5;

int n,m,size[maxn];

Real p,p_,ans,tree[maxn];

std::vector<int>vec[maxn];

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

inline Real poww(Real x,int e)
{
	Real res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x;
		e>>=1;
		x=x*x;
	}
	return res;
}

inline void update(int to,Real x)
{
	while(to<=n)
	{
		tree[to]+=x;
		to+=(to&(-to));
	}
}

inline Real query(int l,int r)
{
	if(l>r)
		return 0;
	Real res=0;
	while(r)
	{
		res+=tree[r];
		r-=(r&(-r));
	}
	l--;
	while(l)
	{
		res-=tree[l];
		l-=(l&(-l));
	}
	return res;
}

int main()
{
	read(n);
	read(m);
	std::cin>>p;
	p_=1-p;
	for(int i=1,a,b;i<=m;i++)
	{
		read(a);
		read(b);
		size[a]++;
		vec[a].push_back(b);
	}
	Real q;
	for(int i=1;i<=n;i++)
	{
		if(!size[i])
			continue;
		std::sort(vec[i].begin(),vec[i].end());
		q=1.0-poww(p_,size[i]);
		for(int v=0;v<size[i];v++)
			ans+=query(vec[i][v]+1,n)*p*poww(p_,v)/q;
		for(int v=0;v<size[i];v++)
			update(vec[i][v],p*poww(p_,v)/q);
	}
	printf("%.2lf\n",(double)ans);
	return 0;
}
