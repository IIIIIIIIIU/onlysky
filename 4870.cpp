#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

int n,k,mod,r;

struct Matrix
{
	int n,m;
	
	ll data[55][55];
	
	Matrix(){}
	
	Matrix(int n_,int m_)
	{
		n=n_;
		m=m_;
		for(int i=1;i<=n;i++)
			for(int v=1;v<=m;v++)
				data[i][v]=0;
	}
	
	inline Matrix operator*(const Matrix &tmp)const
	{
		Matrix res(n,tmp.m);
		for(short i=1,v,e;i<=res.n;i++)
			for(v=1;v<=res.m;v++)
				for(e=1;e<=m;e++)
					(res.data[i][v]+=data[i][e]*tmp.data[e][v])%=mod;
		return res;
	}
};

Matrix poww(Matrix x,ll e)
{
	Matrix res(x.n,x.m);
	for(int i=1;i<=x.n;i++)
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
	std::cin>>n>>mod>>k>>r;
	Matrix base(1,k),t(k,k);
	base.data[1][1]=1;
	for(int i=2;i<=k;i++)
	{
		t.data[i][i]=1;
		t.data[i-1][i]=1;
	}
	t.data[1][1]=1;
	t.data[k][1]+=1;
	base=base*poww(t,1LL*n*k);
	std::cout<<base.data[1][r+1]<<std::endl;
	return 0;
}
