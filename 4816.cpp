#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int mod=1e9+7;
const int maxn=1e6+5;
typedef long long ll;
int pi[maxn],num,mu[maxn];
bool vis[maxn];
ll f[maxn],g[maxn],ci[maxn],di[maxn];
inline void read(int &now)
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
void pre()
{
	mu[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			mu[i]=-1;
		}
		for(int v=1;v<=num&&pi[v]*i<maxn;v++)
		{
			vis[i*pi[v]]=true;
			if(i%pi[v]==0)
				break;
			mu[i*pi[v]]=-mu[i];
		}
	}
}
ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			(res*=x)%=mod;
		(x*=x)%=mod;
		e>>=1;
	}
	return res;
}
int main()
{
	pre();
	f[1]=1;
	g[1]=1;
	ci[1]=1;
	for(int i=2;i<maxn;i++)
	{
		ci[i]=1;
		f[i]=(f[i-1]+f[i-2])%mod;
		g[i]=poww(f[i],mod-2);
	}
	for(int i=1,v,t;i<maxn;i++)
		for(v=1;i*v<maxn;v++)
		{
			if(mu[v]==-1)
				t=g[i];
			else if(mu[v]==1)
				t=f[i];
			else
				t=1;
			(ci[i*v]*=t)%=mod;
		}
	ci[0]=1;
	di[0]=1;
	for(int i=1;i<maxn;i++)
	{
		ci[i]=ci[i-1]*ci[i]%mod;
		di[i]=poww(ci[i],mod-2);
	}
	int T,n,m;
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		ll ans=1;
		for(int i=1,lit=std::min(n,m),nxt;i<=lit;i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			(ans*=poww(ci[nxt]*di[i-1]%mod,1LL*(n/i)*(m/i)))%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
