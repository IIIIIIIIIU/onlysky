#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;

struct Matrix
{
	int n,m;
	
	ll data[12][12];
	
	Matrix(){}
	
	Matrix(int n_,int m_)
	{
		n=n_;
		m=m_;
		for(int i=0;i<=n;i++)
			for(int v=0;v<=m;v++)
				data[i][v]=0;
	}
	
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res(n,tmp.m);
		for(int i=0;i<=res.n;i++)
			for(int v=0;v<=res.m;v++)
				for(int e=0;e<=m;e++)
					res.data[i][v]=(res.data[i][v]+data[i][e]*tmp.data[e][v]%mod)%mod;
		return res;
	}
};

struct Matrix Base(0,11),C(11,11);

int k;

ll Co[11][11],n,ans;

void pre()
{
	Co[0][0]=1;
	for(int i=1;i<=10;i++)
	{
		Co[i][0]=1;
		for(int v=1;v<=i;v++)
			Co[i][v]=(Co[i-1][v-1]+Co[i-1][v])%mod;
	}
}

inline Matrix poww(Matrix x,ll e)
{
	Matrix res(x.n,x.m);
	for(int i=0;i<=x.n;i++)
		res.data[i][i]=1;
	while(e>0)
	{
		if(e&1)
			res=res*x;
		x=x*x;
		e>>=1;
	}
	return res;
}

int main()
{
	pre();
	std::cin>>n>>k;
	n++;
	for(int i=0;i<=10;i++)
		for(int v=0;v<=i;v++)
			C.data[v][i]=Co[i][v];
	Base.data[0][0]=1;
	C.data[k][11]=1;
	C.data[11][11]=2;
	Base=Base*poww(C,n-1);
	ans-=Base.data[0][11];
	Base=Base*C;
	ans+=Base.data[0][11];
	std::cout<<(ans%mod+mod)%mod<<std::endl;
	return 0;
}
