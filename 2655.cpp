#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e3+5;
int A,n,mod;
ll f[maxn][maxn],xi[maxn],yi[maxn];
inline ll poww(ll x,ll e)
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
inline ll li(ll x,int now)
{
	ll res=1;
	for(int i=0;i<=n*2;i++)
		if(i!=now)
			res=res*(x-xi[i])%mod*poww(xi[now]-xi[i],mod-2)%mod;
	return res;
}
int main()
{
	freopen("data.txt","r",stdin);
	std::cin>>A>>n>>mod;
	f[0][0]=1;
	for(int i=1;i<=n*2;i++)
		for(int v=0;v<=n;v++)
			if(v)
				(f[i][v]=f[i-1][v-1]*i*v%mod+f[i-1][v])%=mod;
			else
				f[i][v]=f[i-1][v];
	for(int i=0;i<=n*2;i++)
	{
		xi[i]=i;
		yi[i]=f[i][n];
	}
	ll res=0;
	for(int i=0;i<=n*2;i++)
		(res+=yi[i]*li(A,i)%mod)%=mod;
	std::cout<<(res+mod)%mod<<std::endl;
	return 0;
}
