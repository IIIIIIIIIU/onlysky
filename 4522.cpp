#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

ll e,c,n,d,N,p,q,r;

ll gcd(ll a,ll b)
{
	return !b?a:gcd(b,a%b);
}

inline ll mul(ll x,ll y,ll mod)
{
	ll res=0;
	while(y>0)
	{
		if(y&1)
			res=(res+x)%mod;
		x=(x+x)%mod;
		y>>=1;
	}
	return res%mod;
}
/*
inline ll mul(ll x,ll y,ll mod){
    ll tmp=(x*y-(ll)((long double)x/mod*y+1.0e-8)*mod);
    return tmp<0 ? tmp+mod : tmp;
}
*/

ll getP()
{
	ll c=rand()+3;
	while(true)
	{
		ll x1=1,x2=1,k=2,i=1,D;
		while(true)
		{
			x1=(mul(x1,x1,N)+c)%N;
			D=gcd(std::abs(x1-x2),N);
			if(D>1&&D<N)
				return D;
			if(x1==x2)
				break;
			if(++i==k)
			{
				k<<=1;
				x2=x1;
			}
		}
		c++;
	}
}

inline ll poww(ll x,ll y,ll mod)
{
	ll res=1;
	while(y>0)
	{
		if(y&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		y>>=1;
	}
	return res;
}

ll exgcd(ll l,ll r,ll &x,ll &y)
{
    if(r==0){x=1;y=0;return l;}
    else
    {
        ll w=exgcd(r,l%r,y,x);
        y-=l/r*x;
        return w;
    }
}

ll mod_inverse(ll a,ll m)
{
    ll x,y;
    if(exgcd(a,m,x,y)==1)
        return (x%m+m)%m;
    return -1;
}

int main()
{
	std::cin>>e>>N>>c;
	p=getP();
	q=N/p;
	r=(p-1)*(q-1);
	d=mod_inverse(e,r);
	std::cout<<d<<' '<<poww(c,d,N)<<std::endl;
	return 0;
}
