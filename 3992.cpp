#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const ll maxm=4e4+5;
const ll mod=1004535809;
ll n,m,ai[maxm],X,num,f[maxm],g[maxm],G,bi[maxm],to[maxm];
ll ans[maxm],seq[maxm];
inline void read(ll &now)
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
ll poww(ll x,ll e,ll MOD=mod)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			(res*=x)%=MOD;
		(x*=x)%=MOD;
		e>>=1;
	}
	return res;
}
void NTT(ll *p,ll len,ll opt)
{
	for(ll i=0,v=0;i<len;i++)
	{
		if(i>v)
			std::swap(p[i],p[v]);
		for(ll k=len>>1;(v^=k)<k;k>>=1);
	}
	for(ll h=2;h<=len;h<<=1)
	{
		ll wn=poww(3,mod-1+opt*(mod-1)/h);
		for(ll i=0;i<len;i+=h)
		{
			ll w=1;
			for(ll v=0;v<(h>>1);v++,w=w*wn%mod)
			{
				ll tmp1=p[v+i]%mod;
				ll tmp2=p[v+i+(h>>1)]%mod;
				(p[v+i]=tmp1+tmp2*w)%=mod;
				(p[v+i+(h>>1)]=tmp1-tmp2*w+mod)%=mod;
			}
		}
	}
	if(opt==-1)
	{
		ll inv=poww(len,mod-2);
		for(ll i=0;i<len;i++)
			p[i]=p[i]*inv%mod;
	}
}
ll getG(ll x)
{
	ll k=x-1,cnt=0;
	for(ll i=2;k!=1&&k>=i;i++)
	{
		if(k%i==0)
		{
			bi[++cnt]=i;
			while(k%i==0)
				k/=i;
		}
	}
	for(ll i=2;true;i++)
	{
		bool flag=true;
		for(ll v=1;v<=cnt;v++)
		{
			if(poww(i,(x-1)/bi[v],x)==1)
			{
				flag=false;
				break;
			}
		}
		if(flag)
			return i;
	}
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(X);
	read(num);
	for(ll i=1;i<=num;i++)
	{
		read(ai[i]);
		ai[i]%=m;
	}
	ll len=2;
	while(len<m*2)
		len<<=1;
	G=getG(m);
	f[0]=1;
	g[1]=0;
	for(ll i=1;i<=m-2;i++)
	{
		f[i]=(1LL*f[i-1]*G)%m;
		g[f[i]]=i;
	}
	for(ll i=m-1;i<=m*2-2;i++)
	{
		f[i]=(1LL*f[i-1]*G)%m;
		to[i]=g[f[i]];
	}
	ans[0]=1;
	for(ll i=1;i<=num;i++)
		if(ai[i])
			seq[g[ai[i]]]++;
	while(n>0)
	{
		if(n&1)
		{
			NTT(ans,len,1);
			NTT(seq,len,1);
			for(ll i=0;i<=len;i++)
				(ans[i]*=seq[i])%=mod;
			NTT(ans,len,-1);
			NTT(seq,len,-1);
			for(ll i=m-1;i<=m*2-2;i++)
			{
				(ans[to[i]]+=ans[i])%=mod;
				ans[i]=0;
			}
		}
		NTT(seq,len,1);
		for(ll i=0;i<=len;i++)
			(seq[i]*=seq[i])%=mod;
		NTT(seq,len,-1);
		for(ll i=m-1;i<=m*2-2;i++)
		{
			(seq[to[i]]+=seq[i])%=mod;
			seq[i]=0;
		}
		n>>=1;
	}
	std::cout<<(ans[g[X]]+mod)%mod<<std::endl;
	return 0;
}
