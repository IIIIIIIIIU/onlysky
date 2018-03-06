#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll mod=10000007;

ll n,num[63],dp[63][63][2][2],len,count[63];

bool vis[63][63][2][2];

ll dfs(ll now,ll x,bool g,bool lit)
{
	if(now==1)
		return x==g;
	if(vis[now][x][g][lit])
		return dp[now][x][g][lit];
	vis[now][x][g][lit]=true;
	ll &res=dp[now][x][g][lit];
	if(lit)
	{
		if(!g||(g&&x))
		{
			res+=dfs(now-1,x-g,num[now-1],true);
			if(num[now-1])
				res+=dfs(now-1,x-g,false,false);
		}
	}
	else
	{
		if(!g||(g&&x))
		{
			res+=dfs(now-1,x-g,true,false);
			res+=dfs(now-1,x-g,false,false);
		}
	}
	return res;
}

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		x=x*x%mod;
		e>>=1;
	}
	return res;
}

int main()
{
	std::cin>>n;
	ll x=n;
	while(x>0)
	{
		num[++len]=(x&1);
		x>>=1;
	}
	ll ans=1;
	for(ll i=1;i<=62;i++)
	{
		count[i]+=dfs(len,i,true,true);
		for(ll e=len-1;e>=1;e--)
			count[i]+=dfs(e,i,1,false);
		ans=ans*poww(i,count[i])%mod;
	}
	std::cout<<ans<<std::endl;
	return 0;
}
