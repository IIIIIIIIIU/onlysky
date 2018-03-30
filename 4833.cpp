#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll maxn=3e6+5;

ll T,n,mu[maxn],pi[maxn],num;

ll h[maxn],mod,f[maxn],inv[maxn];

bool vis[maxn];

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

void pre()
{
	mu[1]=1;
	for(ll i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			mu[i]=-1;
		}
		for(ll v=1;v<=num&&i*pi[v]<maxn;v++)
		{
			vis[i*pi[v]]=true;
			if(i%pi[v]==0)
				break;
			mu[i*pi[v]]=-mu[i];
		}
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	pre();
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&mod);
		for(ll i=0;i<=n;i++)
			h[i]=1;
		for(ll i=1;i<=n;i++)
		{
			if(i==1)
				f[i]=1;
			else
				f[i]=(2*f[i-1]+f[i-2])%mod;
			inv[i]=poww(f[i],mod-2);
			for(ll v=1;v*i<=n;v++)
				if(mu[v]==1)
					(h[i*v]*=f[i])%=mod;
				else if(mu[v]==-1)
					(h[i*v]*=inv[i])%=mod;
		}
		ll t=1,ans=0;
		for(ll i=1;i<=n;i++)
		{
			(t*=h[i])%=mod;
			(ans+=t*i%mod)%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
