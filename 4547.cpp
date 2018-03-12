#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll mod=1e7+7;
const ll maxn=1e5+5;

struct Matrix
{
	ll n,m;
	
	ll data[4][4];
	
	Matrix(){}
	
	Matrix(ll n_,ll m_)
	{
		n=n_;
		m=m_;
		for(ll i=1;i<=n;i++)
			for(ll v=1;v<=m;v++)
				data[i][v]=0;
	}
	
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res(n,tmp.m);
		for(short i=1,v,e;i<=res.n;i++)
			for(v=1;v<=res.m;v++)
			{
				for(e=1;e<=m;e++)
					res.data[i][v]+=data[i][e]*tmp.data[e][v]%mod;
				res.data[i][v]%=mod;
			}
		return res;
	}
};

ll n,k,ai[maxn];

ll ans;

Matrix poww(Matrix res,Matrix x,ll e)
{
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
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&ai[i]);
		ans+=ai[i];
	}
	std::sort(ai+1,ai+n+1);
	ll a=ai[n],b=ai[n-1];
	if(a>=0&&b>=0)
	{
		Matrix res(1,3),C(3,3);
		res.data[1][1]=a;
		res.data[1][2]=b;
		C.data[1][1]=1;
		C.data[1][2]=1;
		C.data[1][3]=1;
		C.data[2][1]=1;
		C.data[2][3]=1;
		C.data[3][3]=1;
		res=poww(res,C,k);
		std::cout<<((ans+res.data[1][3])%mod+mod)%mod<<std::endl;
	}
	else if(a>0)
	{
		while(b<=0&&k)
		{
			b+=a;
			(ans+=b)%=mod;
			--k;
		}
		if(a<b)
			std::swap(a,b);
		Matrix res(1,3),C(3,3);
		res.data[1][1]=a;
		res.data[1][2]=b;
		C.data[1][1]=1;
		C.data[1][2]=1;
		C.data[1][3]=1;
		C.data[2][1]=1;
		C.data[2][3]=1;
		C.data[3][3]=1;
		res=poww(res,C,k);
		std::cout<<((ans+res.data[1][3])%mod+mod)%mod<<std::endl;
	}
	else
	{
		(ans+=(a+b)%mod*k%mod)%=mod;
		std::cout<<(ans+mod)%mod<<std::endl;
	}
	return 0;
}
