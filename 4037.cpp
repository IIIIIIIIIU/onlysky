#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=998244353;

struct Matrix
{
	int n,m;
	
	ll data[6][6];

	Matrix(){}
	
	Matrix(const int &n_,const int &m_)
	{
		n=n_;
		m=m_;
		for(short i=1,v;i<=n;i++)
			for(v=1;v<=m;v++)
				data[i][v]=0;
	}
	
	inline Matrix operator*(const Matrix &tmp)const
	{
		Matrix res(n,tmp.m);
		for(register short i=1,v,e;i<=res.n;i++)
			for(v=1;v<=res.m;v++)
			{
				for(e=1;e<=m;e++)
					res.data[i][v]+=data[i][e]*tmp.data[e][v];
				res.data[i][v]%=mod;
			}
		return res;
	}
	
	inline Matrix operator+(const Matrix &tmp)const
	{
		Matrix res(n,m);
		for(register short i=1,v;i<=res.n;i++)
			for(v=1;v<=res.m;v++)
			{
				if((res.data[i][v]=data[i][v]+tmp.data[i][v])>=mod)
					res.data[i][v]-=mod;
			}
		return res;
	}
};

struct Matrix base,zero,val[505][505],g[505],Base[15];

int n,m,num[505];

char str[505];

inline Matrix poww(Matrix x)
{
	x=x*x;
	Matrix res=x;
	x=x*x;
	return res*x*x;
}

int main()
{
	freopen("T1data.txt","r",stdin);
	freopen("T1ans1.txt","w",stdout);
	std::cin>>str+1>>m;
	n=strlen(str+1);
	for(int i=1;i<=n;i++)
		num[i]=str[i]-'0';
	base=Matrix(m,m);
	zero=Matrix(m,m);
	for(int i=1;i<=m;i++)
		zero.data[i][i]=1;
	for(int i=1;i<=m;i++)
		base.data[i][1]=1;
	for(int i=2;i<=m;i++)
		base.data[i-1][i]=1;
	Base[0]=zero;
	for(int i=1;i<=9;i++)
		Base[i]=Base[i-1]*base;
	for(int i=1;i<=n;i++)
	{
		val[i][i]=Base[num[i]];
		for(int v=i+1;v<=n;v++)
			val[i][v]=poww(val[i][v-1])*Base[num[v]];
	}
	g[0]=zero;
	for(int i=1;i<=n;i++)
	{
		g[i].n=m;
		g[i].m=m;
		for(int v=1;v<=i;v++)
			g[i]=g[i]+(g[i-v]*val[i-v+1][i]);
	}
	std::cout<<g[n].data[1][1]<<std::endl;
	return 0;
}
