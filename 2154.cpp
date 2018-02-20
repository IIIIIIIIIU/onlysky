#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const ll maxn=1e7+5;
const ll mod=20101009;
ll n,m,num,pi[maxn];
ll val[maxn];
bool vis[maxn];
void pre()
{
	val[1]=1;
	for(int i=2,v;i<=n;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			val[i]=(i-1LL*i*i)%mod;
		}
		for(v=1;v<=num&&pi[v]*i<=n;v++)
		{
			vis[pi[v]*i]=true;
			if(i%pi[v]==0)
			{
				val[i*pi[v]]=(pi[v]*val[i])%mod;
				break;
			}
			val[i*pi[v]]=(val[pi[v]]*val[i])%mod;
		}
	}
	for(int i=2;i<=n;i++)
		val[i]=(val[i-1]+val[i])%mod;
}
ll sum(ll x,ll y)
{
	return (x*(x+1)/2)%mod*((y*(y+1)/2)%mod)%mod;
}
int main()
{
	std::cin>>n>>m;
	if(n>m)
		std::swap(n,m);
	pre();
	ll ans=0;
	for(ll i=1,nxt;i<=n;i=nxt+1)
	{
		nxt=std::min(n/(n/i),m/(m/i));
		(ans+=sum(n/i,m/i)*(val[nxt]-val[i-1])%mod)%=mod;
	}
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
