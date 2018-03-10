#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=5e5+5;
const int mod=998244353;

int n;

ll a[maxn],b[maxn],f[maxn];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		e>>=1;
		x=x*x%mod;
	}
	return res;
}

ll get(ll x)
{
	if(x==1)
		return n+1;
	int t=n+1;
	return (poww(x,n+1)-1)*poww(x-1,mod-2)%mod;
}

void NTT(ll *p,ll len,ll opt)
{
	for(int i=0,v=0;i<len;i++)
	{
		if(i>v)
			std::swap(p[i],p[v]);
		for(int k=len>>1;(v^=k)<k;k>>=1);
	}
	for(int h=2;h<=len;h<<=1)
	{
		ll wn=poww(3,mod-1+opt*(mod-1)/h);
		for(int v=0;v<len;v+=h)
		{
			ll w=1,tmp1,tmp2;
			for(int e=0;e<(h>>1);e++,w=w*wn%mod)
			{
				tmp1=p[v+e];
				tmp2=p[v+e+(h>>1)];
				p[v+e]=(tmp1+tmp2*w%mod)%mod;
				p[v+e+(h>>1)]=(tmp1-tmp2*w%mod)%mod;
			}
		}
	}
	if(opt==-1)
	{
		ll inv=poww(len,mod-2);
		for(int i=0;i<len;i++)
			p[i]=p[i]*inv%mod;
	}
}

int main()
{
	std::cin>>n;
	a[0]=1;
	b[0]=1;
	ll t=1,inv;
	for(int i=1;i<=n;i++)
	{
		inv=poww(i,mod-2);
		t=t*inv%mod;
		a[i]=a[i-1]*(-inv)%mod;
		b[i]=get(i)*t%mod;
	}
	int len=2;
	while(len<=n*2)
		len<<=1;
	NTT(a,len,1);
	NTT(b,len,1);
	for(int i=0;i<len;i++)
		f[i]=a[i]*b[i]%mod;
	NTT(f,len,-1);
	ll ans=f[0];
	t=1;
	for(int i=1;i<=n;i++)
	{
		t=t*2*i%mod;
		ans=(ans+(t*f[i]%mod))%mod;
	}
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
