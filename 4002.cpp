#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const ll mod=7528443412579576937LL;
inline void add(ll &a,ll b)
{
	if((a+=b)>=mod)
		a-=mod;
}
inline ll mul(ll a,ll b)
{
	ll res=0;
	while(b>0)
	{
		if(b&1)
			add(res,a);
		add(a,a);
		b>>=1;
	}
	return res;
}
struct Matrix
{
	ll n,m,a[3][3];
	Matrix()
	{
		memset(a,0,sizeof(a));
	}
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res;
		res.n=n;
		res.m=tmp.m;
		for(int i=1;i<=res.n;i++)
			for(int v=1;v<=res.m;v++)
			{
				res.a[i][v]=0;
				for(int e=1;e<=m;e++)
					add(res.a[i][v],mul(a[i][e],tmp.a[e][v]));
			}
		return res;
	}
};
Matrix poww(Matrix a,ll e)
{
	Matrix res=a;
	while(e>0)
	{
		if(e&1)
			res=res*a;
		a=a*a;
		e>>=1;
	}
	return res;
}
int main()
{
	ll b,d,n;
	std::cin>>b>>d>>n;
	if(n==0)
	{
		puts("1");
		return 0;
	}
	Matrix a,t;
	a.n=2;
	a.m=2;
	t.n=2;
	t.m=2;
	a.a[1][1]=b;
	a.a[2][1]=2;
	t.a[1][1]=b;
	t.a[1][2]=(d-b*b)>>2;
	t.a[2][1]=1;
	t=poww(t,n-2);
	a=t*a;
	ll ans=a.a[1][1];
	ans-=(d!=b*b&&~n&1);
	std::cout<<ans;
	return 0;
}
