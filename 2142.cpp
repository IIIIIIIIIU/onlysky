#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=7;
ll mod,n,m,w[maxn];
ll poww(ll a,ll b,ll p)
{
	ll res=1;
	while(b>0)
	{
		if(b&1)
			res=res*a%p;
		b>>=1;
		a=a*a%p;
	}
	return res;
}
void exgcd(ll a,ll b,ll &d,ll &x,ll &y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}
ll inv(ll a,ll n)
{
	ll d,x,y;
	exgcd(a,n,d,x,y);
	return d==1?(x+n)%n:-1;
}
ll fac(ll n,ll p,ll pr)
{
	if(n==0)
		return 1;
	ll re=1;
	for(ll i=2;i<=pr;i++)
		if(i%p)
			re=re*i%pr;
	re=poww(re,n/pr,pr);
	ll r=n%pr;
	for(ll i=2;i<=r;i++)
		if(i%p)
			re=re*i%pr;
	return re*fac(n/p,p,pr)%pr;
}
ll C(ll n,ll m,ll p,ll pr)
{
	if(n<m)
		return 0;
	ll x=fac(n,p,pr),y=fac(m,p,pr),z=fac(n-m,p,pr),c=0;
	for(int i=n;i;i/=p)
		c+=i/p;
	for(int i=m;i;i/=p)
		c-=i/p;
	for(int i=n-m;i;i/=p)
		c-=i/p;
	ll a=x*inv(y,pr)%pr*inv(z,pr)%pr*poww(p,c,pr)%pr;
	return a*(mod/pr)%mod*inv(mod/pr,pr)%mod;
}
ll lucas(ll n,ll m)
{
	ll x=mod,re=0;
	for(ll i=2;i<=x;i++)
		if(x%i==0)
		{
			ll pr=1;
			while(x%i==0)
			{
				x/=i;
				pr*=i;
			}
			re=(re+C(n,m,i,pr))%mod;
		}
	return re;
}
int main()
{
	std::cin>>mod>>n>>m;
	ll sum=0;
	for(int i=1;i<=m;i++)
	{
		std::cin>>w[i];
		sum+=w[i];
	}
	if(sum>n)
	{
		puts("Impossible");
		return 0;
	}
	ll ans=1;
	for(int i=1;i<=m;i++)
	{
		ans=ans*lucas(n,w[i])%mod;
		n-=w[i];
	}
	std::cout<<ans<<std::endl;
	return 0;
}
