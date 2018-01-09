#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e7+7;
typedef long long ll;
int n,pi[maxn],phi[maxn],num,p;
bool vis[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
inline void pre()
{
	phi[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			phi[i]=i-1;
		}
		for(int v=1;v<=num&&pi[v]*i<maxn;v++)
		{
			vis[i*pi[v]]=true;
			if(i%pi[v]==0)
			{
				phi[i*pi[v]]=phi[i]*pi[v];
				break;
			}
			else
				phi[i*pi[v]]=phi[i]*(pi[v]-1);
		}
	}
}
inline ll poww(ll x,ll y,ll mod)
{
	ll res=1;
	while(y)
	{
		if(y&1)
			(res*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return res;
}
inline ll f(int x)
{
	if(x==1)
		return 0;
	return poww(2,f(phi[x])+phi[x],x);
}
int main()
{
	pre();
	int T;
	read(T);
	while(T--)
	{
		read(p);
		printf("%lld\n",f(p));
	}
	return 0;
}
