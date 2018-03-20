#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll mod=1e9+7;
const ll maxn=4e6+5;
//const ll maxn=1e2+5;

ll n,m,size,bel[maxn],li[maxn],ri[maxn];
ll num,pi[maxn],phi[maxn];

ll G[maxn],F[maxn],f[maxn],sum[maxn],sum2[maxn];

bool vis[maxn];

void pre()
{
	phi[1]=1;
	for(ll i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			phi[i]=i-1;
		}
		for(ll v=1;v<=num&&i*pi[v]<=n;v++)
		{
			vis[i*pi[v]]=true;
			if(i%pi[v]==0)
			{
				phi[i*pi[v]]=phi[i]*pi[v];
				break;
			}
			phi[i*pi[v]]=phi[i]*(pi[v]-1);
		}
	}
	for(ll i=1;i<=n;i++)
		G[i]=i*i%mod*phi[i]%mod;
	for(ll i=1;i<=n;i++)
		F[i]=(F[i-1]+G[i])%mod;
}

inline void add(ll &x,ll y)
{
	if((x+=y)>=mod)
		x-=mod;
}

inline void mis(ll &x,ll y)
{
	if((x-=y)<0)
		x+=mod;
}

void update(ll pos,ll x)
{
	ll b=bel[pos],t=f[pos];
	for(ll i=b;i<=num;i++)
		mis(sum2[i],t);
	for(ll i=pos;i<=ri[b];i++)
		mis(sum[i],t);
	f[pos]=x%mod;
	t=f[pos];
	for(ll i=b;i<=num;i++)
		add(sum2[i],t);
	for(ll i=pos;i<=ri[b];i++)
		add(sum[i],t);
}

inline ll query(ll pos)
{
	if(!pos)
		return 0;
	return (sum[pos]+sum2[bel[pos]-1])%mod;
}

inline ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}

inline ll getans(ll k)
{
	ll res=0;
	for(ll i=1,r;i<=k;i=r+1)
	{
		r=k/(k/i);
		add(res,(query(r)-query(i-1)+mod)*F[k/i]%mod);
	}
	return (res+mod)%mod;
}

int main()
{
	freopen("data.txt","r",stdin);
	scanf("%lld%lld",&m,&n);
	pre();
	size=std::sqrt(n);
	num=0;
	for(ll i=1;i<=n;i++)
	{
		f[i]=i*i%mod;
		bel[i]=i/size+1;
		if(!li[bel[i]])
			li[bel[i]]=i;
		ri[bel[i]]=i;
		num=bel[i];
	}
	for(ll i=1;i<=num;i++)
	{
		sum[li[i]]=sum2[i]=f[li[i]];
		for(ll v=li[i]+1;v<=ri[i];v++)
		{
			add(sum2[i],f[v]);
			sum[v]=sum[v-1];
			add(sum[v],f[v]);
		}
		add(sum2[i],sum2[i-1]);
	}
	ll x;
	for(ll i=1,a,b,k;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&x,&k);
		ll GCD=gcd(a,b);
		x/=1LL*(a/GCD)*(b/GCD);
		update(GCD,x%mod);
		printf("%lld\n",getans(k));
	}
	return 0;
}
