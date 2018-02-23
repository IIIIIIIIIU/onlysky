#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=1e2+5;
int n,m,k,ui[maxn],ri[maxn],Ri[maxn];
ll fac[maxn],inv[maxn],finv[maxn],f[maxn][maxn],xi[maxn],yi[maxn];
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
inline ll C(int x,int y)
{
	if(x<y||y<0||x<0)
		return 0;
	if(y==0||x==y)
		return 1;
	return fac[x]*finv[y]%mod*finv[x-y]%mod;
}
ll get(ll U,ll R)
{
	ll res=0;
	for(int i=1;i<=U;i++)
		(res+=poww(i,R)*poww(U-i,n-R-1)%mod)%=mod;
	return res;
}
ll li(int v,ll x)
{
	ll res=1;
	for(int i=0;i<=n;i++)
		if(v!=i)
			(res*=(x-xi[i])%mod*poww((xi[v]-xi[i])%mod,mod-2)%mod)%=mod;
	return res;
}
ll solve(ll U,ll R)
{
	for(int i=0;i<=n;i++)
	{
		xi[i]=i;
		yi[i]=get(i,R);
	}
	ll res=0;
	for(int i=0;i<=n;i++)
		(res+=yi[i]*li(i,U)%mod)%=mod;
	return res;
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(k);
	for(int i=1;i<=m;i++)
		read(ui[i]);
	for(int i=1;i<=m;i++)
	{
		read(ri[i]);
		Ri[i]=n-ri[i];
	}
	fac[1]=1;
	for(int i=2;i<=100;i++)
		fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=100;i++)
		inv[i]=poww(i,mod-2);
	finv[1]=1;
	for(int i=2;i<=100;i++)
		finv[i]=finv[i-1]*inv[i]%mod;
	Ri[0]=n-1;
	f[0][n-1]=1;
	for(int i=1;i<=m;i++)
		for(int v=0;v<=Ri[i];v++)
			for(int e=v;e<=Ri[i-1];e++)
				if(n-1-e>=Ri[i]-v)
					(f[i][v]+=C(e,v)*C(n-1-e,Ri[i]-v)%mod*f[i-1][e]%mod)%=mod;
	ll ans=f[m][k];
	for(int i=1;i<=m;i++)
		ans=ans*solve(ui[i],Ri[i])%mod;
	std::cout<<(ans+mod)%mod;
	return 0;
}
