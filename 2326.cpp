#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll n,mod;

struct Matrix
{
	int n,m;
	
	ll ai[4][4];
	
	Matrix()
	{
		n=0;
		m=0;
		for(int i=0;i<4;i++)
			for(int v=0;v<4;v++)
				ai[i][v]=0;
	}
	
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res;
		res.n=n;
		res.m=tmp.m;
		for(int i=1,v,e;i<=res.n;++i)
			for(v=1;v<=res.m;++v)
			{
				res.ai[i][v]=0;
				for(int e=1;e<=res.m;++e)
					(res.ai[i][v]+=ai[i][e]*tmp.ai[e][v])%=mod;
			}
		return res;
	}
};

int len;

int CountLen(ll x)
{
	int res=0;
	while(x)
	{
		res++;
		x/=10;
	}
	return res;
}

Matrix pow(Matrix Base,Matrix c,ll x)
{
	x--;
	while(x>0)
	{
		if(x&1)
			Base=Base*c;
		c=c*c;
		x>>=1;
	}
	return Base;
}

ll poww(int k)
{
	ll res=1;
	while(k--)
		res*=10;
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>n>>mod;
	len=CountLen(n);
	if(len==1)
	{
		ll ans=1;
		for(ll i=2;i<=n;i++)
		{
			ans*=poww(CountLen(i));
			(ans+=i)%=mod;
		}
		std::cout<<ans;
	}
	else
	{
		ll ans=1;
		for(ll i=2;i<10;i++)
		{
			ans*=poww(CountLen(i));
			(ans+=i)%=mod;
		}
		Matrix base;
		base.n=1;
		base.m=3;
		base.ai[1][1]=ans;
		base.ai[1][2]=10;
		base.ai[1][3]=1;
		ll tmp=1;
		for(ll k=2;k<len;k++)
		{
			tmp*=10;
			Matrix c;
			c.n=3;
			c.m=3;
			c.ai[1][1]=poww(k)%mod;
			c.ai[1][2]=0;
			c.ai[1][3]=0;
			c.ai[2][1]=1;
			c.ai[2][2]=1;
			c.ai[2][3]=0;
			c.ai[3][1]=0;
			c.ai[3][2]=1;
			c.ai[3][3]=1;
			base=pow(base,c,tmp*10-tmp+1);
		}
		Matrix c;
		c.n=3;
		c.m=3;
		c.ai[1][1]=poww(len)%mod;
		c.ai[1][2]=0;
		c.ai[1][3]=0;
		c.ai[2][1]=1;
		c.ai[2][2]=1;
		c.ai[2][3]=0;
		c.ai[3][1]=0;
		c.ai[3][2]=1;
		c.ai[3][3]=1;
		tmp*=10;
		base=pow(base,c,n-tmp+2);
		std::cout<<base.ai[1][1]%mod;
	}
	return 0;
}
